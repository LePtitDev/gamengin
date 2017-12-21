#include "uipanel.h"
#include "gameobject.h"
#include "camera.h"
#include "../assets/scene.h"

UIPanel::UIPanel(GameObject *parent) :
    Component(parent)
{

}

void UIPanel::update() {
    Ray ray = Camera::mainCamera->getRay(position.x() + Scene::width / 2, position.y());
    gameObject().transform().setPosition(ray.origin + ray.direction.normalized() * (Camera::mainCamera->zNear + 0.1f));
}

void UIPanel::destroy() {
    removeComponent();
    delete this;
}

void UIPanel::clone(GameObject *c) {
    UIPanel * p = c->addComponent<UIPanel>();
    p->position = position;
}
