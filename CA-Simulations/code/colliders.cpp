#include "colliders.h"
#include <cmath>
#include <iostream>

/*
 * Generic function for collision response from contact plane
 */
void Collider::resolveCollision(Particle* p, const Collision& col, double kElastic, double kFriction, double dt) const
{
    // if particle is static, nothing to do
    if(p->pos - p->prevPos == Vec3(0,0,0)) {
        return;
    }

    Vec3 v_uncorrected = p->vel;
    Vec3 v_n_uncorrected = (col.normal.dot(v_uncorrected)) * col.normal;
    Vec3 v_t_uncorrected = v_uncorrected - v_n_uncorrected;

    Vec3 v_n_corrected = - kElastic * v_n_uncorrected;
    Vec3 v_t_corrected = (1 - kFriction) * v_t_uncorrected;

    Vec3 v_corrected = v_n_corrected + v_t_corrected;

    double new_dt = (p->pos - col.position).norm() / (p->pos - p->prevPos).norm() * dt;

    Vec3 pos_corrected = col.position + new_dt * v_corrected;

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
    return (this->center - p->pos).squaredNorm() < this->radius;
}


bool ColliderSphere::testCollision(const Particle* p, Collision& colInfo) const
{

    Vec3 p0 = p->prevPos;
    Vec3 p1 = p->pos;

    if(p0 == p1) {
        if(this->isInside(p)) {
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

    double tEntry = (- b - std::sqrt(delta)) / (2*a);
    // we only want the smallest one
    //double tExit =  (- b + delta) / (2*a);

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
    // TODO
    return false;
}
bool Particle::testCollision(const Particle* p, Collision& colInfo) const {
    // TODO
    return false;
}
