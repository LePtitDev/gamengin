#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "component.h"

class GameObject;

class ParticleSystem : public Component {

public:

    // Basic constructor
    ParticleSystem(GameObject * parent);

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