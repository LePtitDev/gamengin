#ifndef COMPONENT_H
#define COMPONENT_H

#define COMPONENT_TRANSFORM_ID 0
#define COMPONENT_GEOMETRY_ID 1
#define COMPONENT_MATERIAL_ID 2
#define COMPONENT_PARTICLE_SYSTEM_ID 3

class GameObject;

class Component {

private:

    // GameObject parent
    GameObject * gobject;

public:

    // Basic constructor
    Component(GameObject * parent);

    // Public accessor of the GameObject
    GameObject& gameObject() const;

    // Destroy the component
    virtual void destroy() = 0;

    // Return the component ID
    virtual int component() const = 0;

    // Clone the component in an other GameObject
    virtual void clone(GameObject * c) = 0;

protected:

    // Remove the component in the GameObject
    void removeComponent();

};

#endif // COMPONENT_H
