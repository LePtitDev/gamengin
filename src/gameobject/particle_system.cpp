#include "particle_system.h"
#include "gameobject.h"

ParticleSystem::ParticleSystem(GameObject * parent) : Component(parent) {}

void ParticleSystem::destroy() {
    removeComponent();
    delete this;
}

int ParticleSystem::component() const {
    return COMPONENT_PARTICLE_SYSTEM_ID;
}

void ParticleSystem::clone(GameObject * c) {
    ParticleSystem * p = c->addComponent<ParticleSystem>();
}

bool ParticleSystem::isInstance(Component * c) {
    return (c->component() == COMPONENT_PARTICLE_SYSTEM_ID);
}