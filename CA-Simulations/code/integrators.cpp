#include "integrators.h"


void IntegratorEuler::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    system.setPreviousPositions(system.getPositions()); // used to clip to y=0 (scene particles)
    Vecd x0 = system.getState();
    Vecd dx = system.getDerivative();

    Vecd x1 = x0 + dt*dx;

    system.setState(x1);
    system.setTime(t0+dt);
    system.updateForces();
}


void IntegratorSymplecticEuler::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    system.setPreviousPositions(system.getPositions()); // used to clip to y=0 (scene particles)

    Vecd p0 = system.getPositions();
    Vecd v0 = system.getVelocities();
    Vecd a0 = system.getAccelerations();

    Vecd v1 = v0 + dt * a0;
    Vecd p1 = p0 + dt * v1;

    system.setPositions(p1);
    system.setVelocities(v1);
    system.setTime(t0+dt);
    system.updateForces();
}


void IntegratorMidpoint::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    system.setPreviousPositions(system.getPositions()); // used to clip to y=0 (scene particles)
    Vecd x0 = system.getState();

    // compute a Euler step
    Vecd dxEuler = system.getDerivative();
    Vecd deltaEuler = dt * dxEuler;

    // Evaluate f at the midpoint
    Vecd midPoint = x0 + deltaEuler / 2.0;
    system.setState(midPoint);
    system.setTime(t0 + dt / 2.0);
    system.updateForces();
    Vecd dxMid = system.getDerivative();

    // Take a step using fmid
    Vecd x1 = x0 + dt * dxMid;
    system.setState(x1);
    system.setTime(t0+dt);
    system.updateForces();
}


void IntegratorRK2::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    system.setPreviousPositions(system.getPositions()); // used to clip to y=0 (scene particles)
    Vecd x0 = system.getState();

    // K1: do a Euler step
    Vecd k1 = system.getDerivative();

    // K2: Compute the next Euler step
    system.setTime(t0+dt);
    system.setState(x0 + dt * k1);
    system.updateForces();
    Vecd k2 = system.getDerivative();

    // Compute the new position using the mean of both K
    Vecd x1 = x0 + dt * (k1 + k2) / 2.0;
    system.setState(x1);
    system.setTime(t0+dt); // useless, but kept for clarity only
    system.updateForces();
}


void IntegratorRK4::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    system.setPreviousPositions(system.getPositions()); // used to clip to y=0 (scene particles)
    Vecd x0 = system.getState();

    Vecd k1 = system.getDerivative();

    system.setState(x0 + dt  / 2.0 * k1);
    system.setTime(t0 + dt / 2.0);
    system.updateForces();
    Vecd k2 = system.getDerivative();

    system.setState(x0 + dt  / 2.0 * k2);
    system.setTime(t0 + dt / 2.0); // useless, but kept for clarity only
    system.updateForces();
    Vecd k3 = system.getDerivative();

    system.setState(x0 + dt * k3);
    system.setTime(t0 + dt);
    system.updateForces();
    Vecd k4 = system.getDerivative();

    Vecd x1 = x0 + dt * (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
    system.setState(x1);
    system.setTime(t0+dt); // useless, but kept for clarity only
    system.updateForces();
}

void IntegratorVerlet::step(ParticleSystem &system, double dt) {
    double t0 = system.getTime();
    Vecd p0 = system.getPositions();
    Vecd pNeg1 = (t0 == 0.0 ? p0 - system.getVelocities() * dt : system.getPreviousPositions());
    Vecd a0 = system.getAccelerations();

    const double k = 1.0;
    Vecd p1 = p0 + k * (p0 - pNeg1) + dt * dt * a0;
    Vecd v1 = (p1 - p0) / dt;

    system.setPositions(p1);
    system.setPreviousPositions(p0);
    system.setVelocities(v1);
    system.setTime(t0+dt);
    system.updateForces();
}
