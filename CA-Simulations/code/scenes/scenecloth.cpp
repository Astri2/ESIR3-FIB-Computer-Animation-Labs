#include "scenecloth.h"
#include "glutils.h"
#include "model.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>


SceneCloth::SceneCloth() {
    widget = new WidgetCloth();
    connect(widget, SIGNAL(updatedParameters()), this, SLOT(updateSimParams()));
    connect(widget, SIGNAL(freeAnchors()), this, SLOT(freeAnchors()));
}

SceneCloth::~SceneCloth() {
    if (widget)      delete widget;
    if (shaderPhong) delete shaderPhong;
    if (vaoSphereS)  delete vaoSphereS;
    if (vaoSphereL)  delete vaoSphereL;
    if (vaoCube)     delete vaoCube;
    if (vaoMesh)     delete vaoMesh;
    if (vboMesh)     delete vboMesh;
    if (iboMesh)     delete iboMesh;

    system.deleteParticles();
    if (fGravity)  delete fGravity;
    for (ForceSpring* f : springsStretch) delete f;
    for (ForceSpring* f : springsShear) delete f;
    for (ForceSpring* f : springsBend) delete f;
}

void SceneCloth::initialize() {

    // load shaders
    shaderPhong = glutils::loadShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");
    shaderCloth = glutils::loadShaderProgram(":/shaders/cloth.vert", ":/shaders/cloth.geom", ":/shaders/cloth.frag");

    // create sphere VAOs
    Model sphere = Model::createIcosphere(3);
    vaoSphereL = glutils::createVAO(shaderPhong, &sphere, buffers);
    numFacesSphereL = sphere.numFaces();
    glutils::checkGLError();

    sphere = Model::createIcosphere(1);
    vaoSphereS = glutils::createVAO(shaderPhong, &sphere, buffers);
    numFacesSphereS = sphere.numFaces();
    glutils::checkGLError();

    // create cube VAO
    Model cube = Model::createCube();
    vaoCube = glutils::createVAO(shaderPhong, &cube, buffers);
    glutils::checkGLError();


    // create cloth mesh VAO
    vaoMesh = new QOpenGLVertexArrayObject();
    vaoMesh->create();
    vaoMesh->bind();
    vboMesh = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    vboMesh->create();
    vboMesh->bind();
    vboMesh->setUsagePattern(QOpenGLBuffer::UsagePattern::DynamicDraw);
    vboMesh->allocate(1000*1000*3*3*sizeof(float)); // sync with widget max particles
    shaderCloth->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);
    shaderCloth->enableAttributeArray("vertex");
    iboMesh = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    iboMesh->create();
    iboMesh->bind();
    iboMesh->setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    iboMesh->allocate(1000*1000*2*3*sizeof(unsigned int));
    vaoMesh->release();

    // create gravity force
    fGravity = new ForceConstAcceleration();
    system.addForce(fGravity);

    // In my solution setup, these were the colliders
    colliderBall.setCenter(Vec3(40,-20,0));
    colliderBall.setRadius(30);
    colliderCube.setFromCenterSize(Vec3(-60,-30,0), Vec3(60, 40, 60));
    colliderWalls.setFromCenterSize(Vec3(0, 25, 0), Vec3(200, 200, 200));
}

void SceneCloth::reset()
{
    // we only update numParticles on resets
    updateSimParams();

    // reset particles
    system.deleteParticles();

    // reset forces
    system.clearForces();
    fGravity->clearInfluencedParticles();
    for (ForceSpring* f : springsStretch) delete f;
    springsStretch.clear();
    for (ForceSpring* f : springsShear) delete f;
    springsShear.clear();
    for (ForceSpring* f : springsBend) delete f;
    springsBend.clear();

    // cloth props
    Vec2 dims = widget->getDimensions();
    Vec2i dimParticles = widget->getNumParticles();
    numParticlesX = dimParticles.x();
    numParticlesY = dimParticles.y();
    clothWidth  = dims[0];
    clothHeight = dims[1];
    double edgeX = dims[0]/numParticlesX;
    double edgeY = dims[1]/numParticlesY;
    particleRadius = widget->getParticleRadius();

    // create particles
    numParticles = numParticlesX * numParticlesY;
    fixedParticle = std::vector<bool>(numParticles, false);

    for (int i = 0; i < numParticlesX; i++) {
        for (int j = 0; j < numParticlesY; j++) {

            int idx = i*numParticlesY + j;

            // You can play here with different start positions and/or fixed particles
            fixedParticle[idx] = false;
            if(fixedLogic(i,j)) fixedParticle[idx] = true;

            double tx = i*edgeX - 0.5*clothWidth;
            double ty = j*edgeY - 0.5*clothHeight;

            Vec3 pos = initialSetupVertical ? Vec3(ty+edgeY, 70 - tx - edgeX, 0) : Vec3(ty+edgeY, 70 - edgeX + 0.5*clothWidth, - tx - edgeX);;

            Particle* p = new Particle();
            p->id = idx;
            p->pos = pos;
            p->prevPos = pos;
            p->vel = Vec3(0,0,0);
            p->mass = 1;
            p->radius = particleRadius;
            p->color = Vec3(235/255.0, 51/255.0, 36/255.0);

            system.addParticle(p);
            fGravity->addInfluencedParticle(p);
        }
    }

    // forces: gravity
    system.addForce(fGravity);

    // Code for PROVOT layout
    {
        auto get_part = [this](size_t i, size_t j) {return system.getParticle(i*numParticlesY + j);};
        auto add_spring_force = [this](std::vector<ForceSpring*>& springs, Particle* p, Particle* p1) {
            ForceSpring* f = new ForceSpring;
            f->setParticlePair(p, p1);
            f->setRestLength((p1->pos - p->pos).norm());
            springs.push_back(f);
        };

        // https://imgur.com/a/UMLkXSZ
        for(size_t i = 0 ; i < (size_t)numParticlesX ; ++i) {
            for(size_t j = 0 ; j < (size_t)numParticlesY ; ++j) {
                Particle* p = get_part(i,j);

                // 1. Strech
                if(i < (size_t)numParticlesX - 1) { add_spring_force(springsStretch, p, get_part(i+1,j)); }
                if(j < (size_t)numParticlesY - 1) { add_spring_force(springsStretch, p, get_part(i,j+1)); }

                // 2. Shear
                if(j != (size_t)numParticlesY - 1) {
                    if(i != 0) { add_spring_force(springsShear, p, get_part(i-1,j+1)); }
                    if(i < (size_t)numParticlesX - 1) { add_spring_force(springsShear, p, get_part(i+1,j+1)); }
                }

                // 3. Bend
                if(i < (size_t)numParticlesX - 2) { add_spring_force(springsBend, p, get_part(i+2,j)); }
                if(j < (size_t)numParticlesY - 2) { add_spring_force(springsBend, p, get_part(i,j+2)); }
            }
        }

        // Add all springs into the system
        for(ForceSpring* f : springsStretch) system.addForce(f);
        for(ForceSpring* f : springsShear) system.addForce(f);
        for(ForceSpring* f : springsBend) system.addForce(f);
    }
    updateSprings();

    // update index buffer
    iboMesh->bind();
    numMeshIndices = (numParticlesX - 1)*(numParticlesY - 1)*2*3;
    int* indices = new int[numMeshIndices];
    int idx = 0;
    for (int i = 0; i < numParticlesX-1; i++) {
        for (int j = 0; j < numParticlesY-1; j++) {
            indices[idx  ] = i*numParticlesY + j;
            indices[idx+1] = (i+1)*numParticlesY + j;
            indices[idx+2] = i*numParticlesY + j + 1;
            indices[idx+3] = i*numParticlesY + j + 1;
            indices[idx+4] = (i+1)*numParticlesY + j;
            indices[idx+5] = (i+1)*numParticlesY + j + 1;
            idx += 6;
        }
    }
    void* bufptr = iboMesh->mapRange(0, numMeshIndices*sizeof(int),
                                     QOpenGLBuffer::RangeInvalidateBuffer | QOpenGLBuffer::RangeWrite);
    memcpy(bufptr, (void*)(indices), numMeshIndices*sizeof(int));
    iboMesh->unmap();
    iboMesh->release();
    delete[] indices;
    glutils::checkGLError();
}


void SceneCloth::updateSprings()
{
    double ks = widget->getStiffness();
    double kd = widget->getDamping();

    // here I update all ks and kd parameters.
    // idea: if you want to enable/disable a spring type, you can set ks to 0 for these
    for (ForceSpring* f : springsStretch) {
        f->setSpringConstant(ks);
        f->setDampingCoeff(kd);
    }
    for (ForceSpring* f : springsShear) {
        f->setSpringConstant(ks);
        f->setDampingCoeff(kd);
    }
    for (ForceSpring* f : springsBend) {
        f->setSpringConstant(ks);
        f->setDampingCoeff(kd);
    }
}

void SceneCloth::updateSimParams()
{
    double g = widget->getGravity();
    fGravity->setAcceleration(Vec3(0, -g, 0));

    updateSprings();

    for (Particle* p : system.getParticles()) {
        p->radius = widget->getParticleRadius();
    }

    showParticles = widget->showParticles();

    n_relaxation = widget->getRelaxationSteps();
    alpha_relaxation = widget->getRelaxationAlpha();

    switch(widget->getFixedSetup()) {
    case 0: { // Full top line
        fixedLogic = [this](int i, int j){ return i == 0; };
    } break;
    case 1: { // Partial top line
        fixedLogic = [this](int i, int j){ return i == 0 && (j < 10 || j > this->numParticlesY-11); };
    } break;
    case 2: { // corners
        fixedLogic = [this](int i, int j) {
            return (i < 5 || i > this->numParticlesX-6) && (j < 5 || j > this->numParticlesY-6);
        };
    } break;
    case 3: { // Nothing
        fixedLogic = [this](int i, int j) { return false; };
    } break;
    case 4: { // All
        fixedLogic = [this](int i, int j) { return true; };
    } break;
    default: { // Should not happen
        fixedLogic = nullptr;
    } break;
    }

    int val = widget->getinitialSetup();
    initialSetupVertical = (val == 0);
}

void SceneCloth::freeAnchors()
{
    fixedParticle = std::vector<bool>(numParticles, false);
}

void SceneCloth::paint(const Camera& camera)
{
    QOpenGLFunctions* glFuncs = nullptr;
    glFuncs = QOpenGLContext::currentContext()->functions();

    shaderPhong->bind();
    shaderPhong->setUniformValue("normalSign", 1.0f);

    // camera matrices
    QMatrix4x4 camProj = camera.getPerspectiveMatrix();
    QMatrix4x4 camView = camera.getViewMatrix();
    shaderPhong->setUniformValue("ProjMatrix", camProj);
    shaderPhong->setUniformValue("ViewMatrix", camView);

    // lighting
    const int numLights = 1;
    const QVector3D lightPosWorld[numLights] = {QVector3D(80,80,80)};
    const QVector3D lightColor[numLights] = {QVector3D(1,1,1)};
    QVector3D lightPosCam[numLights];
    for (int i = 0; i < numLights; i++) {
        lightPosCam[i] = camView.map(lightPosWorld[i]);
    }
    shaderPhong->setUniformValue("numLights", numLights);
    shaderPhong->setUniformValueArray("lightPos", lightPosCam, numLights);
    shaderPhong->setUniformValueArray("lightColor", lightColor, numLights);

    // draw the particle spheres
    QMatrix4x4 modelMat;
    if (showParticles) {
        vaoSphereS->bind();
        shaderPhong->setUniformValue("matspec", 1.0f, 1.0f, 1.0f);
        shaderPhong->setUniformValue("matshin", 100.f);
        for (int i = 0; i < numParticles; i++) {
            const Particle* particle = system.getParticle(i);
            Vec3   p = particle->pos;
            Vec3   c = particle->color;
            if (fixedParticle[i])      c = Vec3(63/255.0, 72/255.0, 204/255.0);
            if (i == selectedParticle) c = Vec3(1.0,0.9,0);

            modelMat = QMatrix4x4();
            modelMat.translate(p[0], p[1], p[2]);
            modelMat.scale(particle->radius);
            shaderPhong->setUniformValue("ModelMatrix", modelMat);
            shaderPhong->setUniformValue("matdiff", GLfloat(c[0]), GLfloat(c[1]), GLfloat(c[2]));
            glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereS, GL_UNSIGNED_INT, 0);
        }
    }

    // TODO: draw colliders and walls
    vaoSphereL->bind();
    Vec3 cc = colliderBall.getCenter();
    modelMat = QMatrix4x4();
    modelMat.translate(cc[0], cc[1], cc[2]);
    modelMat.scale(colliderBall.getRadius());
    shaderPhong->setUniformValue("alpha", 1.0f);
    shaderPhong->setUniformValue("ModelMatrix", modelMat);
    shaderPhong->setUniformValue("matdiff", 0.8f, 0.8f, 0.8f);
    shaderPhong->setUniformValue("matspec", 0.0f, 0.0f, 0.0f);
    shaderPhong->setUniformValue("matshin", 0.0f);
    glFuncs->glDrawElements(GL_TRIANGLES, 3*numFacesSphereL, GL_UNSIGNED_INT, 0);

    auto drawAABB = [this, &modelMat, &glFuncs](const ColliderAABB& aabb, float alpha=1.0f) {
        vaoCube->bind();
        Vec3 bmin = aabb.getMin();
        Vec3 bmax = aabb.getMax();
        Vec3 bcenter = 0.5*(bmin + bmax);
        Vec3 bscale = 0.5*(bmax - bmin);
        modelMat = QMatrix4x4();
        modelMat.translate(bcenter[0], bcenter[1], bcenter[2]);
        modelMat.scale(bscale[0], bscale[1], bscale[2]);

        if(alpha != 1.0f) glFuncs->glDepthMask(GL_FALSE);
        shaderPhong->setUniformValue("alpha", alpha);
        shaderPhong->setUniformValue("ModelMatrix", modelMat);
        glFuncs->glDrawElements(GL_TRIANGLES, 3*2*6, GL_UNSIGNED_INT, 0);
        if(alpha != 1.0f) glFuncs->glDepthMask(GL_TRUE);
        shaderPhong->setUniformValue("alpha", 1.0f);
    };

    drawAABB(colliderCube);
    drawAABB(colliderWalls, 0.1f);

    shaderPhong->release();


    // update cloth mesh VBO coords
    vboMesh->bind();
    float* pos = new float[3*numParticles];
    for (int i = 0; i < numParticles; i++) {
        pos[3*i  ] = system.getParticle(i)->pos.x();
        pos[3*i+1] = system.getParticle(i)->pos.y();
        pos[3*i+2] = system.getParticle(i)->pos.z();
    }
    void* bufptr = vboMesh->mapRange(0, 3*numParticles*sizeof(float),
                       QOpenGLBuffer::RangeInvalidateBuffer | QOpenGLBuffer::RangeWrite);
    memcpy(bufptr, (void*)(pos), 3*numParticles*sizeof(float));
    vboMesh->unmap();
    vboMesh->release();
    delete[] pos;

    // draw mesh
    shaderCloth->bind();
    shaderCloth->setUniformValue("ProjMatrix", camProj);
    shaderCloth->setUniformValue("ViewMatrix", camView);
    shaderCloth->setUniformValue("NormalMatrix", camView.normalMatrix());
    shaderCloth->setUniformValue("matdiffFront", 0.7f, 0.0f, 0.0f);
    shaderCloth->setUniformValue("matspecFront", 1.0f, 1.0f, 1.0f);
    shaderCloth->setUniformValue("matshinFront", 100.0f);
    shaderCloth->setUniformValue("matdiffBack", 0.7f, 0.3f, 0.0f);
    shaderCloth->setUniformValue("matspecBack", 0.0f, 0.0f, 0.0f);
    shaderCloth->setUniformValue("matshinBack", 0.0f);
    shaderCloth->setUniformValue("numLights", numLights);
    shaderCloth->setUniformValueArray("lightPos", lightPosCam, numLights);
    shaderCloth->setUniformValueArray("lightColor", lightColor, numLights);
    vaoMesh->bind();
    glFuncs->glDrawElements(GL_TRIANGLES, numMeshIndices, GL_UNSIGNED_INT, 0);
    vaoMesh->release();
    shaderCloth->release();

    glutils::checkGLError();
}


void SceneCloth::update(double dt)
{
    // fixed particles: no velocity, no force acting
    for (int i = 0; i < numParticles; i++) {
        if (fixedParticle[i]) {
            Particle* p = system.getParticle(i);
            p->vel = Vec3(0,0,0);
            p->force = Vec3(0,0,0);
            p->pos = p->prevPos;
        }
    }

    // integration step
    Vecd ppos = system.getPositions();
    integrator.step(system, dt);
    system.setPreviousPositions(ppos);

    // fixed particles: no velocity, no force acting
    for (int i = 0; i < numParticles; i++) {
        if (fixedParticle[i]) {
            Particle* p = system.getParticle(i);
            p->vel = Vec3(0,0,0);
            p->force = Vec3(0,0,0);
            p->pos = p->prevPos;
        }
    }

    Collision colInfo;
    // user interaction
    if (selectedParticle >= 0) {
        Particle* p = system.getParticle(selectedParticle);
        p->prevPos = p->pos;
        p->pos = cursorWorldPos;
        p->vel = Vec3(0,0,0);

        // TODO: test and resolve for collisions during user movement
        if(checkCollisions) {
            if (colliderBall.testCollision(p, colInfo)) {
                colliderBall.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }

            if (colliderCube.testCollision(p, colInfo)) {
                colliderCube.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }

            if (colliderWalls.testCollision(p, colInfo)) {
                colliderWalls.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }
        }

        p->prevPos = p->pos;
        p->vel = Vec3(0,0,0);
    }


    auto applyRelaxation = [this, dt](std::vector<ForceSpring*>& springs) {
        for(ForceSpring* spring : springs) {
            Particle* p1 = spring->getParticle1();
            Particle* p2 = spring->getParticle2();

            Vec3 d = p2->pos - p1->pos;
            double len = d.norm();
            double rest = spring->getRestLength();
            double diff = len - rest;

            // relax only if the spring is over extended
            if(diff <= 0) continue;

            // alpha is a factor [0,1] to reduce the effect of the relaxation
            Vec3 correction = alpha_relaxation * diff * d.normalized();
            // If one particle is fixed, the other takes the full correction
            if(fixedParticle[p1->id]) {
                // if the other is also fixed, nothing happens
                if(!fixedParticle[p2->id]) {
                    p2->pos -= correction;

                    // Correct velocities using euler
                    p2->vel = (p2->pos - p2->prevPos)/dt;
                }
            }
            else if(fixedParticle[p2->id]) {
                // p1 can't be fixed here (if, else if)
                p1->pos += correction;

                // Correct velocities using euler
                p1->vel = (p1->pos - p1->prevPos)/dt;
            }
            // Otherwise they both take half of it
            else {
                p1->pos += 0.5 * correction;
                p2->pos -= 0.5 * correction;

                // Correct velocities using euler
                p1->vel = (p1->pos - p1->prevPos)/dt;
                p2->vel = (p2->pos - p2->prevPos)/dt;
            }

        }
    };


    // Apply n times relaxation on all the springs
    // Order should not be important ?
    for(int _ = 0 ; _ < n_relaxation ; _++) {
        applyRelaxation(springsStretch);
        applyRelaxation(springsShear);
        applyRelaxation(springsBend);
    }

    // TODO collisions
    for (Particle* p : system.getParticles()) {
        if(checkCollisions) {
            if (colliderBall.testCollision(p, colInfo)) {
                colliderBall.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }

            if (colliderCube.testCollision(p, colInfo)) {
                colliderCube.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }

            if (colliderWalls.testCollision(p, colInfo)) {
                colliderWalls.resolveCollision(p, colInfo, colBounce, colFriction, dt);
            }
        }
    }

    // needed after we have done collisions and relaxation, since spring forces depend on p and v
    system.updateForces();
}


void SceneCloth::mousePressed(const QMouseEvent* e, const Camera& cam)
{
    grabX = e->pos().x();
    grabY = e->pos().y();

    if (!(e->modifiers() & Qt::ControlModifier)) {

        Vec3 rayDir = cam.getRayDir(grabX, grabY); // normalized
        Vec3 origin = cam.getPos();

        selectedParticle = -1;
        double minSquaredDist = std::numeric_limits<double>::max();

        for (int i = 0; i < numParticles; i++) {
            // squaredNorm: avoid computing the squareroots
            double dist2 = ((system.getParticle(i)->pos - origin).cross(rayDir)).squaredNorm();

            if(dist2 < minSquaredDist) {
                minSquaredDist = dist2;
                selectedParticle = i;
            }
        }

        /*
        // if you aimed too poorly, don't select anything
        double distThreshold = 4 * system.getParticle(selectedParticle)->radius;
        if(minSquaredDist > distThreshold * distThreshold) {
            selectedParticle = -1;
        }
        */

        if (selectedParticle >= 0) {
            cursorWorldPos = system.getParticle(selectedParticle)->pos;
        }
    }
}

void SceneCloth::mouseMoved(const QMouseEvent* e, const Camera& cam)
{
    int dx = e->pos().x() - grabX;
    int dy = e->pos().y() - grabY;
    grabX = e->pos().x();
    grabY = e->pos().y();

    if (e->modifiers() & Qt::ControlModifier) {

    }
    else if (e->modifiers() & Qt::ShiftModifier) {

    }
    else {
        if (selectedParticle >= 0) {
            double d = -(system.getParticle(selectedParticle)->pos - cam.getPos()).dot(cam.zAxis());
            Vec3 disp = cam.worldSpaceDisplacement(dx, -dy, d);
            cursorWorldPos += disp;
        }
    }
}

void SceneCloth::mouseReleased(const QMouseEvent*, const Camera&)
{
    selectedParticle = -1;
}

void SceneCloth::keyPressed(const QKeyEvent* e, const Camera&)
{
    if (selectedParticle >= 0 && e->key() == Qt::Key_F) {
        fixedParticle[selectedParticle] = true;
        Particle* p = system.getParticle(selectedParticle);
        p->prevPos = p->pos;
        p->vel = Vec3(0,0,0);
        p->force = Vec3(0,0,0);
    }
}
