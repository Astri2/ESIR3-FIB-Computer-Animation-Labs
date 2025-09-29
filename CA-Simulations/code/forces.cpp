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

    double L = this->getRestLength();
    double k_s = this->getSpringConstant(); // most likely k_e
    double k_d = this->getDampingCoeff();

    Vecd P2_1 = p2->pos - p1->pos;
    double P2_1_norm = P2_1.norm();
    Vecd P2_1_normalized = P2_1 / P2_1_norm;

    Vecd F1 = (k_s * (P2_1_norm - L) + k_d * (p2->vel - p1->vel).dot(P2_1_normalized)) * P2_1_normalized;
    Vecd F2 = - F1;

    p1->force += F1;
    p2->force += F2;
}

void ForceGravitation::apply() {
    // j (affected)
    // i is the attractor
    const Particle* prt_i = this->getAttractor();
    for (Particle* prt_j : particles) {
        Vecd Pi_j = prt_i->pos - prt_j->pos;
        double Pi_j_norm = Pi_j.norm();
        double squared_norm = Pi_j_norm * Pi_j_norm;
        Vecd Pi_j_normalized = Pi_j / Pi_j_norm;

        double smoothing_factor = (2 / (1 + exp(- this->a * squared_norm / (this->b*this->b)))) - 1;

        prt_j->force += (this->G * prt_i->mass * prt_j->mass) / squared_norm * smoothing_factor * Pi_j_normalized;
    }
}
