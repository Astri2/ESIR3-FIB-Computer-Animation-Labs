#include "colliders.h"
#include <cmath>
#include <iostream>


#define SPEED4POS 0

/*
 * Generic function for collision response from contact plane
 */
void Collider::resolveCollision(Particle* p, const Collision& col, double kElastic, double kFriction, double dt)
{
    // if particle is static, nothing to do
    if(p->pos - p->prevPos == Vec3(0,0,0)) {
        return;
    }

    // New Speed
    Vec3 v_uncorrected = p->vel;
    Vec3 v_n_uncorrected = (col.normal.dot(v_uncorrected)) * col.normal;
    Vec3 v_t_uncorrected = v_uncorrected - v_n_uncorrected;

    Vec3 v_n_corrected = - kElastic * v_n_uncorrected;
    Vec3 v_t_corrected = (1 - kFriction) * v_t_uncorrected;

    Vec3 v_corrected = v_n_corrected + v_t_corrected;


    // I have issues with that one. Particle tend to pass through colliders...
# if SPEED4POS // use new speed to compute new position
    double new_dt = (p->pos - col.position).norm() / (p->pos - p->prevPos).norm() * dt;
    Vec3 pos_corrected = col.position + new_dt * v_corrected;
# else // Don't use new speed to compute new position
    double d = - col.normal.dot(col.position);

    // compute the distance to the plane (which is negative because we're inside the plane)
    double h = col.normal.dot(p->pos) + d;

    // compute tengential movement
    Vec3 dp = p->pos - col.position;
    Vec3 dpN = col.normal.dot(dp) * col.normal;
    Vec3 dpT = dp - dpN;

    Vec3 pos_corrected = p->pos - (1 + kElastic) * h * col.normal - kFriction * dpT;

#endif

    p->pos = pos_corrected;
    p->vel = v_corrected;
}



/*
 * Plane
 */
bool ColliderPlane::isInside(const Particle* p) const
{
    Vec3 normal = this->planeN;
    Vec3 pos = p->pos;
    return normal.dot(pos) + this->planeD <= 0;
}


bool ColliderPlane::testCollision(const Particle* p, Collision& colInfo) const
{
    Vec3 p0 = p->prevPos;
    Vec3 p1 = p->pos;
    Vec3 dir = (p1 - p0);

    Vec3 normal = this->planeN;
    double d = this->planeD;

    // if direction is parallel to plane, check if it is inside
    if(normal.dot(dir) == 0.0) {
        if(this->isInside(p)) {
            colInfo.normal = normal;
            colInfo.position = p0;
            return true;
        } else return false;
    }

    double tEntry = -(normal.dot(p0) + d) / (normal.dot(dir));

    // ensure the intersection is on the segment.
    if(tEntry < 0.0 || tEntry > 1.0) {
        return false;
    }

    colInfo.normal = normal;
    colInfo.position = p0 + dir * tEntry;

    return true;
}



/*
 * Sphere
 */
bool ColliderSphere::isInside(const Particle* p) const
{
    // Empty ball
    return (this->center - p->pos).squaredNorm() == this->radius * this->radius;
}


bool ColliderSphere::testCollision(const Particle* p, Collision& colInfo) const
{

    Vec3 p0 = p->prevPos;
    Vec3 p1 = p->pos;

    if(p0 == p1) {
        if(isInside(p)) {
            colInfo.normal = (p0 - this->center).normalized();
            colInfo.position = p0;
            return true;
        } else return false;
    }

    Vec3 dir = p1 - p0;

    Vec3 C = this->center;
    double r = this->radius;

    double a = dir.dot(dir);
    double b = 2 * dir.dot(p0 - C);
    double c = C.dot(C) + p0.dot(p0) - 2 * p0.dot(C) - r*r;

    double delta = b*b - 4*a*c;

    if(delta < 0.0) {
        return false;
    }

    // we want the smallest positive one
    double tEntry = (- b - std::sqrt(delta)) / (2*a);
    if(tEntry < 0) { tEntry = (- b + std::sqrt(delta)) / (2*a); }

    // ensure the intersection is on the segment. Not sure this can happen
    if(tEntry < 0.0 || tEntry > 1.0) {
        return false;
    }

    Vec3 entryPoint = p0 + tEntry * dir;
    Vec3 normal = (entryPoint - C).normalized();

    colInfo.position = entryPoint;
    colInfo.normal = normal;
    return true;
}



/*
 * AABB
 */

static bool isInsideAABB(Vec3 pos, Vec3 min, Vec3 max) {
    return
        (min[0] <= pos[0] && pos[0] <= max[0]) &&
        (min[1] <= pos[1] && pos[1] <= max[1]) &&
        (min[2] <= pos[2] && pos[2] <= max[2]);
}

bool ColliderAABB::isInside(const Particle* p) const
{
    Vec3 min = this->getMin();
    Vec3 max = this->getMax();
    Vec3 pos = p->pos;

    return isInsideAABB(pos, min, max);
}


bool ColliderAABB::testCollision(const Particle* p, Collision& colInfo) const
{

    Vec3 p0 = p->prevPos;
    Vec3 p1 = p->pos;
    Vec3 dir = p1 - p0;


    double tEnter = 0.0;
    double tExit = 1.0;
    Vec3 normal(0,0,0);

    Vec3 bbMin = this->getMin();
    Vec3 bbMax = this->getMax();

    // AABB are "empty", so that we can simulate walls
    if(isInsideAABB(p0, bbMin, bbMax) && isInsideAABB(p1, bbMin, bbMax)) return false;

    // particle was inside and tries to escape
    if(isInsideAABB(p0, bbMin, bbMax) && !isInsideAABB(p1, bbMin, bbMax)) {
        std::swap(p0, p1);
        dir *= -1;
    }

    for(int i = 0 ; i < 3 ; i++) {
        // check parallel to axis
        if(dir[i] == 0) {
            // if the parralel line is not between the two planes, no intersection
            if (p0[i] < bbMin[i] || p0[i] > bbMax[i]) return false;
        }
        else {
            double t0 = (bbMin[i] - p0[i]) / dir[i];
            double t1 = (bbMax[i] - p0[i]) / dir[i];

            if(t0 > t1) std::swap(t0, t1);

            // if t0 == tEnter, I should average the normal on both axis, but float comparison sucks so I won't
            if (t0 > tEnter) {
                tEnter = t0;
                // update the normal
                normal = Vec3(0,0,0);
                // if the direction is going down, the normal is up. Vice Versa
                normal[i] = (dir[i] < 0) ? 1.0 : -1.0;
            }

            tExit = std::min(tExit, t1);

            if (tEnter > tExit) return false; // No overlap
        }
    }

    // should never proc, but ensures the detection is on range of the segment
    if(tEnter < 0.0 || tEnter > 1.0) {
        return false; // Collision outside movement range
    }

    colInfo.normal = normal;
    colInfo.position = p0 + dir * tEnter;
    return true;
}

bool Particle::isInside(const Particle* p) const {
    return (this->pos - p->pos).squaredNorm() <= (this->radius + p->radius) * (this->radius + p->radius);
}
bool Particle::testCollision(const Particle* p, Collision& colInfo) const {
    if((this->pos - p->pos).squaredNorm() > (this->radius + p->radius) * (this->radius + p->radius))
        return false;

    // don't consider movement
    colInfo.normal = (p->pos - this->pos).normalized();
    colInfo.position = this->pos + (this->radius + p->radius) * colInfo.normal;
    return true;

    // same logic as the sphere ?
    // d(p0 + lambda*v0, p1 + lambda*v1)^2 = (r0+r1)^2
    // (p0 + lambda*v0 - p1 - lambda*v1) . (p0 + lambda*v0 - p1 - lambda*v1)^T - (r0+r1)^2 = 0
    // (p0 - p1 + lambda*(v0-v1)) . (p0 - p1 + lambda*(v0-v1))^T - (r0+r1)^2 = 0
    // (dp      + lambda*dv     ) . (dp      + lambda*dv     )^T - r      ^2 = 0
    // dp^2 + 2*dp*dv*lambda + dv^2*lambda^2 - r^2 = 0
    // a = dv^2
    // b = 2*dp*dv
    // c = dp^2 - dr^2
    // d = 4*dp^2*dv^2 - 4*dv^2*(dp^2-r^2)
    // d = 4*dv^2*r^2  always > 0. must be all wrong :)
}
