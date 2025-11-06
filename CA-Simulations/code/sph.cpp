#include "sph.h"

#include <math.h>

#include <iostream>

SPH::SPH(size_t maxParticles, float particleRadius, float h, float cs, float rho0, float mu, float maxPressure):
    m_particleHash(7*particleRadius, 2*maxParticles, maxParticles),
    m_densities(maxParticles, -1),
    m_pressures(maxParticles, -1),
    m_h(h), m_cs(cs), m_rho0(rho0), m_mu(mu),
    m_maxPressure(maxPressure)
{}

void SPH::apply() {
    // 1. update neighbors hashmap
    m_particleHash.update(&this->particles);

    for(Particle* pi : this->particles) {
        float rho = 0.f;
        // 1. query neighbors
        for(const Particle* pj : m_particleHash.query(pi, m_h)) {
            Vec3 r = (pj->pos - pi->pos);
            if(r.norm() > m_h) continue;

            rho += pj->mass * Wpoly6(r , m_h);
        }

        // 2. compute density
        m_densities[pi->id] = rho;
        // 3. compute pressure
        // adding a max cap. I also need a min cap or the simulation explodes.
        // But then the succion effect does not work anymore
        m_pressures[pi->id] = std::clamp(m_cs*m_cs*(rho-m_rho0), 0.f, m_maxPressure);
    }

    /*
    float rho_avg = 0, rho_min = 10000, rho_max = -10000;
    for (auto* p : particles) {
        rho_avg += m_densities[p->id];
        rho_min = std::min(rho_min, m_densities[p->id]);
        rho_max = std::max(rho_max, m_densities[p->id]);
    }
    rho_avg /= particles.size();
    std::cout << "rho avg/min/max: " << rho_avg  << "/" << rho_min << "/" << rho_max << std::endl;

    float p_avg = 0, p_min = 10001, p_max = -10001;
    for (auto* p : particles) {
        p_avg += m_pressures[p->id];
        p_min = std::min(p_min, m_pressures[p->id]);
        p_max = std::max(p_max, m_pressures[p->id]);
    }

    p_avg /= particles.size();
    std::cout << "p avg/min/max: " << p_avg  << "/" << p_min << "/" << p_max << std::endl;

    //this->drawPressure(0, 1000);
    */

    // 4. add forces
    // only applying density & viscosity because interaction & gravity are handled by their own
    for(Particle* pi : this->particles) {
        Vec3 a_p(0.f, 0.f, 0.f);
        Vec3 a_v(0.f, 0.f, 0.f);

        float rho_i = m_densities[pi->id];
        float press_i = m_pressures[pi->id];
        float frac_i = press_i / (rho_i*rho_i);
        for(const Particle* pj : m_particleHash.query(pi, m_h)) {
            if(pi == pj) continue;
            Vec3 r = (pj->pos - pi->pos);
            if(r.norm() > m_h) continue;

            // 4.1 pressure acceleration
            float rho_j = m_densities[pj->id];
            float press_j = m_pressures[pj->id];
            float frac_j = press_j / (rho_j*rho_j);

            // I am desesperate, I asked ChatGPT and it told me to remove the minus sign
            // I know it is not ok anymore, but for some reason it seems to work better...
            float Pij = pj->mass * (frac_i + frac_j);

            // norm shoud not be 0 for spiky (skip pi==pj)

            a_p += Pij * this->GradWSpiky(r, m_h);

            // 4.2 viscosity acceleration
            // 0 if v_i = v_j => can skip skip pi==pj safely
            Vec3 Vij = m_mu * pj->mass * (pj->vel - pi->vel) / (rho_i * rho_j);
            a_v += Vij * this->LapWVisco(r, m_h);
        }

        // apply force
        pi->force += pi->mass * (a_p + a_v);
    }
}

void SPH::drawDensity(float min, float max) {
    for(Particle* pi : this->particles) {
        float u = (m_densities[pi->id] - min) / (max - min);
        pi->color = Vec3(u, 0, 1-u);
    }
}

void SPH::drawPressure(float min, float max) {
    for(Particle* pi : this->particles) {
        float u = (m_pressures[pi->id] - min) / (max - min);
        pi->color = Vec3(u, 0, 1-u);
    }
}

inline float SPH::Wpoly6(Vec3 r, float h) const {
    float r_norm = r.norm();
    if(r_norm > h) return 0;
    return 315.f / (64.f * M_PI * std::pow(h, 9)) * std::pow((h*h - r_norm*r_norm), 3);
}

inline Vec3 SPH::GradWSpiky(Vec3 r, float h) const {
    float r_norm = r.norm();
    if(r_norm > h) return {0.f, 0.f, 0.f};
    return -r * 45.f / (M_PI * std::pow(h, 6) * r_norm) * std::pow(h-r_norm, 2.f);
}
inline float SPH::LapWVisco(Vec3 r, float h) const {
    float r_norm = r.norm();
    if(r_norm > h) return 0;
    return 45.f / (M_PI * std::pow(h, 5)) * (1 - r_norm/h);
}
