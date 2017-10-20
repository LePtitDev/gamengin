#include "camera.h"
#include "gameobject.h"

Camera * Camera::mainCamera = 0;

Camera::Camera(GameObject *parent) :
    Component(parent),
    perspective(true),
    fov(45.0f),
    zNear(0.1f),
    zFar(30.0f),
    aspect(16.0f / 9.0f),
    Perspective(perspective),
    FOV(fov),
    Near(zNear),
    Far(zFar),
    Aspect(aspect),
    Projection(projection)
{
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
    if (mainCamera == 0)
        mainCamera = this;
}

QMatrix4x4 Camera::getProjection() const {
    return projection;
}

void Camera::toggleView() {
    perspective = !perspective;
    calculateProjection();
}

void Camera::toggleView(bool p) {
    perspective = p;
    calculateProjection();
}

void Camera::setFOV(float f) {
    fov = f;
    calculateProjection();
}

void Camera::setNear(float n) {
    zNear = n;
    calculateProjection();
}

void Camera::setFar(float f) {
    zFar = f;
    calculateProjection();
}

void Camera::setAspect(float a) {
    aspect = a;
    calculateProjection();
}

void Camera::lookAt(QVector3D pos) {
    Transform& t = gameObject().transform();
    t.rotation = QQuaternion::fromDirection(pos - t.position, QVector3D(0.0f, 1.0f, 0.0f));
    calculateProjection();
}

void Camera::destroy() {
    removeComponent();
    delete this;
}

int Camera::component() const {
    return COMPONENT_CAMERA_ID;
}

void Camera::clone(GameObject *c) {
    Camera * cam = c->addComponent<Camera>();
    cam->perspective = perspective;
    cam->fov = fov;
    cam->zNear = zNear;
    cam->zFar = zFar;
    cam->aspect = aspect;
    cam->projection = projection;
}

bool Camera::isInstance(Component *c) {
    return (c->component() == COMPONENT_CAMERA_ID);
}

void Camera::calculateProjection() {
    projection.setToIdentity();
    if (perspective)
        projection.perspective(fov, aspect, zNear, zFar);
    else
        projection.ortho(-2.0f * aspect, 2.0f * aspect, -2.0f, 2.0f, zNear, zFar);
    Transform& t = gameObject().transform();
    projection.lookAt(t.position, t.position + t.rotation * QVector3D(0.0f, 0.0f, 1.0f), t.rotation * QVector3D(0.0f, 1.0f, 0.0f));
}
