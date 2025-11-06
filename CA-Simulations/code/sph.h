#ifndef SPH_H
#define SPH_H

#include <cstdio>
#include <vector>

#include "particle.h"
#include "ParticleHash.h"
#include "forces.h"

class SPH: public Force
{
public:
    SPH(size_t maxParticle, float particleRadius, float h, float cs, float rho0, float mu, float maxPressure = 1000.f);
    virtual ~SPH() {}

    virtual void apply();


    // debug purpose
    void drawDensity(float min, float max);
    void drawPressure(float min, float max);

protected:
    ParticleHash m_particleHash;

    std::vector<float> m_densities;
    std::vector<float> m_pressures;
    const float m_h, m_cs, m_rho0, m_mu;
    const float m_maxPressure;

    inline float Wpoly6(Vec3 r, float h) const; // density
    inline Vec3 GradWSpiky(Vec3 r, float h) const; // pressure
    inline float LapWVisco(Vec3 r, float h) const; // visco
};

#endif // SPH_H
