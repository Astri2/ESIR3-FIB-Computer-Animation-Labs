#include "ParticleHash.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <random>

// #include <iostream>

ParticleHash::ParticleHash(float spacing, size_t tableSize, size_t maxEntries):
    m_spacing(spacing),
    m_tableSize(tableSize),
    m_maxEntries(maxEntries),
    m_cellStart(tableSize + 1, 0),
    m_cellEntries(maxEntries, 0),
    m_queryIds(maxEntries, 0),
#if HASH_FIX
    m_queryChecked(tableSize + 1, false),
#endif
    m_particles(nullptr)
{
    assert(m_spacing > 0 && "spacing must be positive.");
    assert(m_tableSize > 0 && "table size can't be 0");
    assert(m_maxEntries > 0 && "maxEntries can't be 0");
}

void ParticleHash::update(const std::vector<Particle*>* particles) {
    assert(particles != nullptr && "particles pointer can't be null.");
    assert(particles->size() <= m_cellEntries.size() && "You can't pass more particles than maxEntries.");

    m_particles = particles;

    // reset cellStart vector. Other vector don't need to be reset because values will be overriden
    std::fill(m_cellStart.begin(), m_cellStart.end(), 0);

    // 1. Count
    for(Particle* p : *m_particles) {
        size_t h = hashP(p);
        m_cellStart[h]++;
    }

    // 2. Partial sum
    // include guard. Because guard is always 0 at this point
    for(size_t i = 1 ; i < m_cellStart.size() ; i++) {
        m_cellStart[i] += m_cellStart[i-1];
    }

    // 3. Fill in
    for(Particle* p : *m_particles) {
        size_t h = hashP(p);
        m_cellStart[h]--;
        m_cellEntries[m_cellStart[h]] = p;
    }
}

const std::vector<Particle*>& ParticleHash::query(const Particle* p, float maxDist) {
    assert(m_particles != nullptr && "DataStructure must be updated before queried");

    // Compute min cell indexes
    int x0 = intCoords(p->pos[0] - maxDist);
    int y0 = intCoords(p->pos[1] - maxDist);
    int z0 = intCoords(p->pos[2] - maxDist);
    // Compute max cell indexes
    int x1 = intCoords(p->pos[0] + maxDist);
    int y1 = intCoords(p->pos[1] + maxDist);
    int z1 = intCoords(p->pos[2] + maxDist);

    m_queryIds.clear();


#if HASH_FIX
    std::fill(m_queryChecked.begin(), m_queryChecked.end(), false);
#endif

    // iterate through all selected cells
    for(int x = x0 ; x <= x1 ; x++) {
        for(int y = y0 ; y <= y1 ; y++) {
            for(int z = z0 ; z <= z1 ; z++) {
                // TODO: ensure this works, I'm not sure of my c++ skills
                size_t h = hash(x, y, z);
                // std::cout << h << std::endl;
                size_t start = m_cellStart[h];
                size_t end   = m_cellStart[h + 1];
#if HASH_FIX
                // avoid adding the same cell multiple times
                if(m_queryChecked[h]) continue;
                m_queryChecked[h] = true;
#endif
                // no realloc because capacity is big enough already
                m_queryIds.insert(
                    m_queryIds.end(),
                    m_cellEntries.begin() + start,
                    m_cellEntries.begin() + end // interval is exclusive
                );
            }
        }
    }

    return m_queryIds;
}

size_t ParticleHash::hash(int x, int y, int z) const {
    // formula taken from Matthias Müller's video.
    int h = (x*92837111) ^ (y*689287499) ^ (z*283923481);
    return std::abs(h) % m_tableSize;
}

int ParticleHash::intCoords(float x) const {
    return std::floor(x / m_spacing);
}

size_t ParticleHash::hashP(const Particle* p) const {
    return hash(
        intCoords(p->pos[0]),
        intCoords(p->pos[1]),
        intCoords(p->pos[2])
    );
}

static Vec3 hashToRGB(int n) {
    std::mt19937 rng(n); // seed the random generator with the integer
    std::uniform_int_distribution<int> dist(0, 255);
    return Vec3(dist(rng) / 255.0, dist(rng) / 255.0, dist(rng) / 255.0);
}

void ParticleHash::showHash() {
    for(Particle* p : *m_particles) {
        p->color = hashToRGB(hashP(p));
    }
}
