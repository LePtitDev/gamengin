#include "component.h"

#include "gameobject.h"

Component::Component(GameObject *parent) : gobject(parent) {}

GameObject& Component::gameObject() const {
    return *gobject;
}

void Component::removeComponent() {
    gobject->removeComponent(this);
}
