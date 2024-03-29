#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "component.h"
#include "../geometry/mesh.h"

#include <vector>
#include <random>

#include <QTime>

class GameObject;

class ParticleSystem : public Component {

    // Particle emitter
    Mesh * particleEmitter;

    // Particle instance
    GameObject * particleInstance;

    // Particle list
    std::vector<GameObject *> particles;

    // Particle creation time
    std::vector<int> ptimes;

    // Particle timer
    QTime timer;

    // Number of particles created
    unsigned long createdCount;

    // Randomizer
    std::default_random_engine randomizer;

public:

    // Maximal particles count
    unsigned int MaxParticleCount;

    // Particle creation frequency
    unsigned int ParticleFrequency;

    // Life particle duration (in milliseconds)
    unsigned int ParticleDuration;

    // Basic constructor
    ParticleSystem(GameObject * parent);

    // Update callback
    virtual void update() override;
    
    // Assign the particle emitter
    bool assignEmitter(const char * name);

    // Assign the particle instance
    bool assignParticle(const char * name);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // PARTICLE_SYSTEM_H
