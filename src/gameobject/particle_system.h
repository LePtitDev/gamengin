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
    Mesh particleEmitter;

    // Particle instance
    GameObject * particleInstance;

    // Particle list
    std::vector<GameObject *> particles;

    // Particle creation time
    std::vector<int> ptimes;

    // Particle timer
    QTime timer;

    // Last creation time
    int last_creation;

    // Randomizer
    std::default_random_engine randomizer;

public:

    // Maximal particles count
    unsigned int MaxParticleCount;

    // Delay between 2 particle creations (in milliseconds)
    unsigned int ParticleDelay;

    // Life particle duration (in milliseconds)
    unsigned int ParticleDuration;

    // Basic constructor
    ParticleSystem(GameObject * parent);

    // Start callback
    void start();

    // Update callback
    void update();
    
    // Assign the particle emitter
    void setEmitter(Mesh * mesh);

    // Assign the particle instance
    void setParticle(GameObject * g);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual int component() const override;

    // Component override
    virtual void clone(GameObject * c) override;

    // Indicate if the componant is an instance of ParticleSystem
    static bool isInstance(Component * c);

};

#endif // PARTICLE_SYSTEM_H