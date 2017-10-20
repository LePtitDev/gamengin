#include "component.h"

#include "gameobject.h"

Component::Component(GameObject *parent) : gobject(parent) {}

GameObject& Component::gameObject() const {
    return *gobject;
}

void Component::update() {}

void Component::removeComponent() {
    gobject->removeComponent(this);
}
