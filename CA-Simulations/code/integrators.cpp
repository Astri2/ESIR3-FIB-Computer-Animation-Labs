#include "integrators.h"


void IntegratorEuler::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd x0 = system.getState();
    Vecd dx = system.getDerivative();
    Vecd x1 = x0 + dt*dx;
    system.setState(x1);
    system.setTime(t0+dt);
    system.updateForces();
}


void IntegratorSymplecticEuler::step(ParticleSystem &system, double dt) {
    // TODO
}


void IntegratorMidpoint::step(ParticleSystem &system, double dt) {
    // TODO
}


void IntegratorRK2::step(ParticleSystem &system, double dt) {
    // TODO
}


void IntegratorRK4::step(ParticleSystem &system, double dt) {
    // TODO
}


void IntegratorVerlet::step(ParticleSystem &system, double dt) {
    // TODO
}
