#include "particle_system.h"
#include "gameobject.h"
#include "../assets/assets.h"

#include <QVector3D>

ParticleSystem::ParticleSystem(GameObject * parent) :
    Component(parent),
    particleInstance(0),
    MaxParticleCount(2000),
    ParticleFrequency(1000),
    ParticleDuration(640),
    particleEmitter(0),
    createdCount(0)
{

}

void ParticleSystem::update() {
    if (!timer.isValid()) {
        timer.start();
        return;
    }
    if (particleInstance == 0 || particleEmitter == 0 || particleEmitter->vertexCount() == 0)
        return;
    int time = timer.msecsTo(timer.currentTime());
    while (ptimes.size() > 0 && ptimes[0] + (int)ParticleDuration < time) {
        particles[0]->destroy();
        particles.erase(particles.begin());
        ptimes.erase(ptimes.begin());
    }
    int needCreate = (int)(((unsigned long)time * (unsigned long)ParticleFrequency / (unsigned long)1000) - createdCount);
    for (int i = 0; i < needCreate && particles.size() < MaxParticleCount; i++, createdCount++) {
        ptimes.push_back(time);
        GameObject * g = new GameObject();
        particleInstance->clone(g);
        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (particleEmitter->trianglesCount() > 0) {
            unsigned int triangle = randomizer() % particleEmitter->trianglesCount();
            float t0 = dis(randomizer);
            float t1 = dis(randomizer) * (1.0f - t0);
            float t2 = 1.0f - t0 - t1;
            QVector3D pos = particleEmitter->getVertex(particleEmitter->getTriangle(triangle)[0]) * t0 + particleEmitter->getVertex(particleEmitter->getTriangle(triangle)[1]) * t1 + particleEmitter->getVertex(particleEmitter->getTriangle(triangle)[2]) * t2;
            g->transform().localPosition += pos;
        }
        else {
            g->transform().localPosition += particleEmitter->getVertex(randomizer() % particleEmitter->vertexCount());
        }
        particles.push_back(g);
        gameObject().addChild(g);
    }
}

bool ParticleSystem::assignEmitter(const char * name) {
    particleEmitter = 0;
    Asset * asset = Asset::Find(name);
    if (asset == 0 || asset->getData<Mesh>() == 0)
        return false;
    particleEmitter = asset->getData<Mesh>();
    return true;
}

bool ParticleSystem::assignParticle(const char * name) {
    particleInstance = 0;
    Asset * asset = Asset::Find(name);
    if (asset == 0 || asset->getData<GameObject>() == 0)
        return false;
    particleInstance = asset->getData<GameObject>();
    return true;
}

void ParticleSystem::destroy() {
    if (particleInstance != 0)
        particleInstance->destroy();
    for (size_t i = 0, sz = particles.size(); i < sz; i++)
        particles[i]->destroy();
    removeComponent();
    delete this;
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
    p->createdCount = createdCount;
    p->randomizer = randomizer;
    p->MaxParticleCount = MaxParticleCount;
    p->ParticleFrequency = ParticleFrequency;
    p->ParticleDuration = ParticleDuration;
}
