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

void Transform::clone(GameObject * c) {
    Transform * t = c->addComponent<Transform>();
    t->position = position;
    t->rotation = rotation;
    t->scale = scale;
}
