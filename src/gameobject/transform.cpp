#include "transform.h"
#include "gameobject.h"

Transform::Transform(GameObject *parent) :
    Component(parent),
    scale(1.0f, 1.0f, 1.0f)
{

}

void Transform::destroy() {
    removeComponent();
    delete this;
}

int Transform::component() const {
    return COMPONENT_TRANSFORM_ID;
}

bool Transform::isInstance(Component * c) {
    return (c->component() == COMPONENT_TRANSFORM_ID);
}
