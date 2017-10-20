#ifndef MATERIAL_H
#define MATERIAL_H

#include "component.h"

class Material : public Component {

public:

    // Basic constructor
    Material(GameObject * parent);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual int component() const override;

    // Component override
    virtual void clone(GameObject * c) override;

    // Indicate if the componant is an instance of Geometry
    static bool isInstance(Component * c);

};

#endif // MATERIAL_H
