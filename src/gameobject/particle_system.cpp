#include "particle_system.h"
#include "gameobject.h"

#include <QVector3D>

ParticleSystem::ParticleSystem(GameObject * parent) :
    Component(parent),
    particleInstance(0),
    MaxParticleCount(100),
    ParticleDelay(100),
    ParticleDuration(5000),
    last_creation(0)
{

}

void ParticleSystem::start() {
    timer.start();
}

void ParticleSystem::update() {
    if (particleInstance == 0 || particleEmitter.vertexCount() == 0)
        return;
    int time = timer.msec();
    while (ptimes.size() > 0 && ptimes[0] + ParticleDuration < time) {
        particles[0]->destroy();
        particles.erase(particles.begin());
        ptimes.erase(ptimes.begin());
    }
    if (last_creation + (int)ParticleDelay < time) {
        ptimes.push_back(time);
        GameObject * g = new GameObject();
        if (particleEmitter.trianglesCount() > 0) {
            unsigned int triangle = randomizer() % particleEmitter.trianglesCount();
            float maxR = (unsigned int)-1;
            float t0 = maxR / (float)randomizer();
            float t1 = (maxR / (float)randomizer()) * (1.0f - t0);
            float t2 = (maxR / (float)randomizer()) * (1.0f - t0 - t1);
            QVector3D pos = particleEmitter.getVertex(particleEmitter.getTriangle(triangle)[0]) * t0 + particleEmitter.getVertex(particleEmitter.getTriangle(triangle)[1]) * t1 + particleEmitter.getVertex(particleEmitter.getTriangle(triangle)[2]) * t2;
            g->transform().position = pos;
        }
        else {
            g->transform().position = particleEmitter.getVertex(randomizer() % particleEmitter.trianglesCount());
        }
        particles.push_back(g);
        gameObject().addChild(g);
        last_creation = time;
    }
}

void ParticleSystem::setEmitter(Mesh * m) {
    particleEmitter = *m;
}

void ParticleSystem::setParticle(GameObject * g) {
    if (particleInstance != 0)
        particleInstance->destroy();
    particleInstance = g;
}

void ParticleSystem::destroy() {
    if (particleInstance != 0)
        particleInstance->destroy();
    for (size_t i = 0, sz = particles.size(); i < sz; i++)
        particles[i]->destroy();
    removeComponent();
    delete this;
}

int ParticleSystem::component() const {
    return COMPONENT_PARTICLE_SYSTEM_ID;
}

void ParticleSystem::clone(GameObject * c) {
    ParticleSystem * p = c->addComponent<ParticleSystem>();
    p->particleEmitter = particleEmitter;
    p->particleInstance = new GameObject();
    particleInstance->clone(p->particleInstance);
    for (size_t i = 0, sz = particles.size(); i < sz; i++) {
        p->particles.push_back(new GameObject());
        particles[i]->clone(p->particles[i]);
        p->ptimes.push_back(ptimes[i]);
    }
    p->timer = timer;
    p->last_creation = last_creation;
    p->randomizer = randomizer;
    p->MaxParticleCount = MaxParticleCount;
    p->ParticleDelay = ParticleDelay;
    p->ParticleDuration = ParticleDuration;
}

bool ParticleSystem::isInstance(Component * c) {
    return (c->component() == COMPONENT_PARTICLE_SYSTEM_ID);
}