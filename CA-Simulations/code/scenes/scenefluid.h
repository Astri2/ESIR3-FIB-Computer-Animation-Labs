#ifndef SCENEFLUID_H
#define SCENEFLUID_H

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <list>
#include "scene.h"
#include "widgetfluid.h"
#include "particlesystem.h"
#include "integrators.h"
#include "colliders.h"
#include "ParticleHash.h"
#include "sph.h"

class SceneFluid : public Scene
{
    Q_OBJECT

public:
    SceneFluid();
    virtual ~SceneFluid();

    virtual void initialize();
    virtual void reset();
    virtual void update(double dt);
    virtual void paint(const Camera& cam);

    virtual void mousePressed(const QMouseEvent* e, const Camera& cam);
    virtual void mouseMoved(const QMouseEvent* e, const Camera& cam);

    virtual void getSceneBounds(Vec3& bmin, Vec3& bmax) {
        bmin = Vec3(-110, -10, -110);
        bmax = Vec3( 110, 100,  110);
    }

    virtual unsigned int getNumParticles() { return system.getNumParticles(); }

    virtual QWidget* sceneUI() { return widget; }

public slots:
    void updateSimParams();

protected:
    WidgetFluid* widget = nullptr;

    QOpenGLShaderProgram* shader = nullptr;
    QOpenGLVertexArrayObject* vaoSphereL = nullptr;
    QOpenGLVertexArrayObject* vaoCube    = nullptr;
    unsigned int numFacesSphereL = 0;

    IntegratorSymplecticEuler integrator;
    ParticleSystem system;

    // Force sources
    ForceConstAcceleration* fGravity;
    SPH* fSPH;

    std::vector<ColliderAABB> m_colliderBoxes;
    ColliderAABB* colliderFloor;

    double kBounce, kFriction;

    // ParticleHash* m_particleHash;

    double Pmass, Pradius, h, cs, rho0, mu;
    int Sradius, Lwater;

    int mouseX, mouseY;
};

#endif // SCENEFLUID_H
