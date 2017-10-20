#include "material.h"
#include "gameobject.h"

Material::Material(GameObject *parent) : Component(parent) {}

void Material::destroy() {
    removeComponent();
    delete this;
}

int Material::component() const {
    return COMPONENT_MATERIAL_ID;
}

void Material::clone(GameObject *c) {
    Material * m = c->addComponent<Material>();
}

bool Material::isInstance(Component *c) {
    return (c->component() == COMPONENT_MATERIAL_ID);
}
