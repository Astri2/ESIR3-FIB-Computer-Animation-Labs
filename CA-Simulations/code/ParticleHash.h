#pragma once

#include <vector>
#include "particle.h"

/**
 * @brief The ParticleHash class will hash particle positions in order to find neighbors in a smaller time than O^2
 *
 * tutorial video from Matthias Müller: https://www.youtube.com/watch?v=D2M8jTtKi44
 * spacing:
 * - type: float
 * - usage : size of a cell in the grid
 * tableSize:
 * - type: int
 * - usage : store the size of the table
 * QuerySize:
 * - type: int
 * - usage: store the size of a query
 * tableArray (cellStart):
 * - type: vector<int>
 * - size: tableSize +1 (guard)
 * - usage: store indices of start of cells
 * ParticleArray (cellEntries):
 * - type: vector<int>
 * - size: maximum number of particles
 * - usage: store pointers to particles
 * QueryIds:
 * - type: vector<int>
 * - size: maximum number of particles (if a query finds everyone)
 * - usage : store the result of a query
 * ======
 * Create:
 * - 1. Count: For each particle, compute its hash and increment the associated value in tableArray
 * - 2. Partial sum: in tableArray, t[x] = t[x] + t[x-1]
 * - 3. Fill in: On each particle: compute its hash, decrement by 1 the cell associated in tableArray. Then put the particle in particleArray at the indice the the new value of tableArray
 *
 * Query:
 * - Get the indices of min_cell and max_cell (matching distance critera)
 * - for each cell, compute the hash
 * - We get the indice of the begin of cellEntries in cellStarts[h] and the indice of the end in cellStart[h+1] (this is why guard cell is important)
 * - add each included particle in QueryIds and set QuerySize to this number of particles. (Use of memcpy?)
 * ==
 * Note:
 * - We can create the hash table at each iteration (O(n))
 * - for each particle, we first query it, then read the queryIds. Don't forget to still check particle to particle distances (or use intCoords ? Anyway, Distance check = safer)
 */
#define HASH_FIX 1

class ParticleHash {
protected:
    const float m_spacing;
    const size_t m_tableSize;
    const size_t m_maxEntries;
    std::vector<size_t> m_cellStart;
    std::vector<Particle*> m_cellEntries;
    std::vector<Particle*> m_queryIds;
#if HASH_FIX
    std::vector<bool> m_queryChecked;
#endif

    const std::vector<Particle*>* m_particles;

    size_t hash(int x, int y, int z) const;
    int intCoords(float x) const;

public:
    ParticleHash(float spacing, size_t tableSize, size_t maxEntries);

    void update(const std::vector<Particle*>* particles);

    void showHash();

    const std::vector<Particle*>& query(const Particle* p, float maxDist);

    // public for debug purposes. TODO: set private
    size_t hashP(const Particle* p) const;
};
