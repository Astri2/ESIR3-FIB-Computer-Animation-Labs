#include "scenefluid.h"
#include "glutils.h"
#include "model.h"
#include <QOpenGLFunctions_3_3_Core>

SceneFluid::SceneFluid(): fSPH(nullptr)/*, m_particleHash(nullptr)*/, colliderFloor(nullptr) {
    widget = new WidgetFluid();
    connect(widget, SIGNAL(updatedParameters()), this, SLOT(updateSimParams()));
}

SceneFluid::~SceneFluid() {
    if (widget)     delete widget;
    if (shader)     delete shader;
    if (vaoSphereL) delete vaoSphereL;
    if (vaoCube)    delete vaoCube;
    if (fGravity)   delete fGravity;
    // if(m_particleHash) {delete m_particleHash; m_particleHash = nullptr; }
    if(fSPH) {delete fSPH; fSPH = nullptr; }
}

void SceneFluid::initialize() {
    // load shader
    shader = glutils::loadShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");

    // create particle VAOs
    Model sphereLowres = Model::createIcosphere(1);
    vaoSphereL = glutils::createVAO(shader, &sphereLowres, buffers);
    numFacesSphereL = sphereLowres.numFaces();
    glutils::checkGLError();

    // create box VAO
    Model cube = Model::createCube();
    vaoCube = glutils::createVAO(shader, &cube, buffers);
    glutils::checkGLError();

    // create forces
    fGravity = new ForceConstAcceleration();

    Vec3 center = {0., 0., 0.};
    float side = 200.;
    float halfSide = side / 2.;
    float wallWidth = 2.;
    float wallHeight = 60.;
    float bottomHeight = 2.;

    m_colliderBoxes.reserve(5);

    // floor
    m_colliderBoxes.push_back({center + Vec3(-halfSide, 0, -halfSide), center + Vec3( halfSide, bottomHeight,  halfSide)});
    colliderFloor = &(m_colliderBoxes[0]); // keep a ptr to it to move it later :)

    // walls
    m_colliderBoxes.push_back({center + Vec3(-halfSide, 0, -halfSide), center + Vec3( -halfSide + wallWidth, wallHeight,  halfSide)});
    m_colliderBoxes.push_back({center + Vec3(-halfSide, 0, -halfSide), center + Vec3( halfSide, wallHeight,  -halfSide + wallWidth)});
    m_colliderBoxes.push_back({center + Vec3(-halfSide, 0, halfSide- wallWidth), center + Vec3( halfSide, wallHeight,  halfSide)});
    m_colliderBoxes.push_back({center + Vec3(halfSide - wallWidth, 0, -halfSide), center + Vec3( halfSide, wallHeight,  halfSide)});

}

void SceneFluid::reset()
{
    // update values from UI
    updateSimParams();

    // reset random seed
    Random::seed(1337);

    fGravity->clearInfluencedParticles();
    if(fSPH) fSPH->clearInfluencedParticles();
    system.clearForces();
    system.deleteParticles();

    int particleCounter = 0;
    const double spawnSpacing = 2.2 * this->Pradius;


    // 1. Bubble
    // create a floating bubble
    // /*
    {
        Vec3 center = {0., 80., 0.};
        // float radius = 10.05;
        float radius = this->Sradius;

        for(double x = center[0]-radius ; x <= center[0]+radius ; x+=spawnSpacing) {
            for(double y = center[1]-radius ; y <= center[1]+radius ; y+=spawnSpacing) {
                for(double z = center[2]-radius ; z <= center[2]+radius ; z+=spawnSpacing) {
                    Vec3 pos = {(double)x, (double)y, (double)z};
                    if((center - pos).norm() > radius) continue;

                    Particle* p = new Particle();
                    p->pos = pos;
                    p->id = particleCounter++;
                    p->prevPos = pos;
                    p->vel = Vec3(0,0,0);
                    p->mass = 10.0f;
                    p->radius = this->Pradius;
                    p->color = Vec3(36/255.0, 51/255.0, 235/255.0);

                    system.addParticle(p);
                    fGravity->addInfluencedParticle(p);
                }
            }
        }
    }
    // */

    // 2. still water
    // /*
    {
        // box constants
        // TODO: make a struct in .h
        Vec3 center = {0., 0., 0.};
        float side = 200.;
        float halfSide = side / 2.;
        float wallWidth = 2.;
        float wallHeight = 60.;
        float bottomHeight = 2.;

        const float minX = center[0] - halfSide + wallWidth + spawnSpacing / 2.;
        const float maxX = center[0] + halfSide - wallWidth - spawnSpacing / 2.;
        const float minZ = center[2] - halfSide + wallWidth + spawnSpacing / 2.;
        const float maxZ = center[2] + halfSide - wallWidth - spawnSpacing / 2.;

        for(int row = 0 ; row < this->Lwater ; row++) {
            for(double x = minX ; x < maxX ; x+=spawnSpacing) {
                for(double z = minZ ; z < maxZ ; z+=spawnSpacing) {
                    double y = center[1] + bottomHeight + spawnSpacing / 2. + row * spawnSpacing;
                    Vec3 pos = {x, y, z};

                    Particle* p = new Particle();
                    p->pos = pos;
                    p->id = particleCounter++;
                    p->prevPos = pos;
                    p->vel = Vec3(0,0,0);
                    p->mass = 12.0f;
                    p->radius = this->Pradius;
                    p->color = Vec3(120/255.0, 120/255.0, 235/255.0);

                    system.addParticle(p);
                    fGravity->addInfluencedParticle(p);
                }
            }
        }
    }
    // */

    // float spacing = 2*this->Pradius;
    // if(m_particleHash) { delete m_particleHash; m_particleHash = nullptr;}
    // m_particleHash = new ParticleHash(spacing, particleCounter, 2*particleCounter);

    // assuming fGravity is not null because apparently checking pointers is optionnal in this code base
    system.addForce(fGravity);

    if(fSPH) { delete fSPH; fSPH = nullptr;}
    fSPH = new SPH(particleCounter, this->Pradius, this->h, this->cs, this->rho0, this->mu);
    system.addForce(fSPH);
    for(Particle* p : system.getParticles()) {
        // adding it only now because I needed the number of particles to create the force object...
        // yes my design is kinda bad...
        fSPH->addInfluencedParticle(p);
    }
}

void SceneFluid::updateSimParams()
{
    // get gravity from UI and update force
    double g = widget->getGravity();
    fGravity->setAcceleration(Vec3(0, -g, 0));

    if(colliderFloor != nullptr) {
        // if "valve" is open, shift the floor to create a hole
        Vec3 center = colliderFloor->getCenter();
        center[0] = widget->isValveOpen() ? -50 : 0;
        colliderFloor->setFromCenterSize(center, colliderFloor->getSize());
    }

    // get other relevant UI values and update simulation params
    kBounce = 0.5;
    kFriction = 0.1;

    Pmass = widget->getPmass();
    Pradius = widget->getPradius();
    h = widget->getH();
    cs = widget->getCs();
    rho0 = widget->getRho0();
    mu = widget->getMu();
    Sradius = widget->getSradius();
    Lwater = widget->getLwater();
}


void SceneFluid::paint(const Camera& camera) {

    QOpenGLFunctions* glFuncs = nullptr;
    glFuncs = QOpenGLContext::currentContext()->functions();

    shader->bind();

    // camera matrices
    QMatrix4x4 camProj = camera.getPerspectiveMatrix();
    QMatrix4x4 camView = camera.getViewMatrix();
    shader->setUniformValue("ProjMatrix", camProj);
    shader->setUniformValue("ViewMatrix", camView);

    // lighting
    const int numLights = 1;
    const QVector3D lightPosWorld[numLights] = {QVector3D(100,500,100)};
    const QVector3D lightColor[numLights] = {QVector3D(1,1,1)};
    QVector3D lightPosCam[numLights];
    for (int i = 0; i < numLights; i++) {
        lightPosCam[i] = camView.map(lightPosWorld[i]);  // map = matrix * vector
    }
    shader->setUniformValue("numLights", numLights);
    shader->setUniformValueArray("lightPos", lightPosCam, numLights);
    shader->setUniformValueArray("lightColor", lightColor, numLights);


    QMatrix4x4 modelMat;

    // draw the particles
    vaoSphereL->bind();
    for (const Particle* particle : system.getParticles()) {
        Vec3   p = particle->pos;
        Vec3   c = particle->color;
        double r = particle->radius;

        modelMat = QMatrix4x4();
        modelMat.translate(p[0], p[1], p[2]);
        modelMat.scale(r);
        shader->setUniformValue("ModelMatrix", modelMat);

        shader->setUniformValue("matdiff", GLfloat(c[0]), GLfloat(c[1]), GLfloat(c[2]));
        shader->setUniformValue("matspec", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("matshin", 100.f);

        glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereL, GL_UNSIGNED_INT, 0);
    }
    vaoSphereL->release();

    // draw box
    vaoCube->bind();
    float alpha = 0.2f;
    shader->setUniformValue("matdiff", 0.4f, 0.8f, 0.4f);
    shader->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
    shader->setUniformValue("matshin", 0.0f);
    if(alpha != 1.0f) {
        shader->setUniformValue("alpha", alpha);
        glFuncs->glDepthMask(GL_FALSE);
    }

    for(const ColliderAABB& box : m_colliderBoxes) {
        Vec3 cc = box.getCenter();
        Vec3 hs = 0.5*box.getSize();
        modelMat = QMatrix4x4();
        modelMat.translate(cc[0], cc[1], cc[2]);
        modelMat.scale(hs[0], hs[1], hs[2]);
        shader->setUniformValue("ModelMatrix", modelMat);
        glFuncs->glDrawElements(GL_TRIANGLES, 3*2*6, GL_UNSIGNED_INT, 0);
    }
    if(alpha != 1.0f) {
        glFuncs->glDepthMask(GL_TRUE);
        shader->setUniformValue("alpha", 1.0f);
    }
    vaoCube->release();

    shader->release();
}

void SceneFluid::update(double dt) {
    // integration step
    Vecd ppos = system.getPositions();
    integrator.step(system, dt);
    system.setPreviousPositions(ppos);

    // collisions
    Collision colInfo;

    // disabling particle-particle collisions for now
    /*
    m_particleHash->update(&system.getParticles());
    for(Particle* p : system.getParticles()) {
        for(const Particle* partCollider : m_particleHash->query(p, 2*p->radius)) {
            if(p == partCollider) continue;

            if(partCollider->testCollision(p, colInfo)) {
                Collider::resolveCollision(p, colInfo, kBounce, kFriction, dt);
            }
        }
    }
    */

    for(const ColliderAABB& box : m_colliderBoxes) {
        for (Particle* p : system.getParticles()) {
            if (box.testCollision(p, colInfo)) {
                Collider::resolveCollision(p, colInfo, kBounce, kFriction, dt);
            }
        }
    }
}

void SceneFluid::mousePressed(const QMouseEvent* e, const Camera&)
{
    mouseX = e->pos().x();
    mouseY = e->pos().y();
}

void SceneFluid::mouseMoved(const QMouseEvent* e, const Camera& cam)
{
    int dx = e->pos().x() - mouseX;
    int dy = e->pos().y() - mouseY;
    mouseX = e->pos().x();
    mouseY = e->pos().y();

    Vec3 disp = cam.worldSpaceDisplacement(dx, -dy, cam.getEyeDistance());
}
