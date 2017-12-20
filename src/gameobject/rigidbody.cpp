#include "rigidbody.h"
#include "gameobject.h"

Rigidbody::Rigidbody(GameObject *parent) :
    Component(parent),
    gravity(0.0f, -1.0f, 0.0f)
{

}

void Rigidbody::update() {
    if (!timer.isValid()) {
        timer.start();
        return;
    }
    float time = (float)timer.elapsed() / 1000.0f;
    velocity += gravity * (9.81f * time);
    gameObject().transform().localPosition += velocity * time;
    timer.restart();
}

void Rigidbody::destroy() {
    removeComponent();
    delete this;
}

void Rigidbody::clone(GameObject *c) {
    Rigidbody * r = c->addComponent<Rigidbody>();
    r->gravity = gravity;
    r->velocity = velocity;
}
