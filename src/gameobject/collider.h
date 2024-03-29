#ifndef COLLIDER_H
#define COLLIDER_H

#include "component.h"
#include "gameobject.h"
#include "../geometry/bounds.h"

#include <vector>

class Collider : public Component {

public:

    // Basic constructor
    Collider(GameObject * parent) : Component(parent) {}

    // Destructor
    virtual ~Collider() {}

    // Get bounds
    virtual Bounds bounds() const = 0;

    // Does ray intersect this ?
    virtual bool intersectRay(const Ray& ray, float& distance) const = 0;

    // Component override
    virtual void destroy() override = 0;

    // Component override
    virtual void clone(GameObject * g) override = 0;

    // Send a raycast in the scene and get touched collider and their distance
    static std::vector<std::pair<Collider *, float>> Raycast(const Ray& ray);

};

#endif // COLLIDER_H
