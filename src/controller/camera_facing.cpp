#include "camera_facing.h"
#include "../gameobject/gameobject.h"
#include "../gameobject/camera.h"

CameraFacingController::CameraFacingController(GameObject *parent) : Component(parent) {}

void CameraFacingController::update() {
    gameObject().transform().setRotation(QQuaternion::fromDirection(gameObject().transform().position() - Camera::mainCamera->gameObject().transform().position(), QVector3D(0.0f, 1.0f, 0.0f)));
}

void CameraFacingController::destroy() {
    removeComponent();
    delete this;
}

void CameraFacingController::clone(GameObject *c) {
    c->addComponent<CameraFacingController>();
}
