#include "forces.h"
#include <iostream>
void ForceConstAcceleration::apply() {
    for (Particle* p : particles) {
        p->force += p->mass * this->getAcceleration();
    }
}

void ForceDrag::apply() {
    for (Particle* p : particles) {
        p->force +=
            - this->getLinearCoefficient() * p->vel
            - this->getQuadraticCoefficient() * p->vel.norm() * p->vel;
    }
}

void ForceSpring::apply() {
    if (particles.size() < 2) return;
    Particle* p1 = getParticle1();
    Particle* p2 = getParticle2();

    // TODO
}
