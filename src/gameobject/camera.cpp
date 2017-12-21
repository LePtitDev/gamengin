#include "camera.h"
#include "gameobject.h"
#include "../assets/scene.h"

Camera * Camera::mainCamera = 0;

Camera::Camera(GameObject *parent) :
    Component(parent),
    perspective(true),
    fov(45.0f),
    zNear(0.1f),
    zFar(50.0f),
    aspect(16.0f / 9.0f)
{
    if (mainCamera != 0) {
        fov = mainCamera->fov;
        zNear = mainCamera->zNear;
        zFar = mainCamera->zFar;
        aspect = mainCamera->aspect;
    }
    mainCamera = this;
}

Ray Camera::getRay(int mouse_x, int mouse_y) const {
    float x = (2.0f * (float)mouse_x) / Scene::width - 1.0f;
    float y = 1.0f - (2.0f * (float)mouse_y) / Scene::height;
    float z = 1.0f;
    QVector3D ray_nds(x, y, z);
    QVector4D ray_clip(ray_nds.x(), ray_nds.y(), -1.0, 1.0);
    QVector4D ray_eye = getProjection().inverted() * ray_clip;
    ray_eye.setZ(-1.0);
    ray_eye.setW(0.0);
    QVector4D ray_wor4 = (getView().inverted() * ray_eye);
    QVector3D ray_wor = QVector3D(ray_wor4.x(), ray_wor4.y(), ray_wor4.z()).normalized();
    return Ray(gameObject().transform().position(), ray_wor);
}

void Camera::toggleView() {
    perspective = !perspective;
}

QMatrix4x4 Camera::getProjection() const {
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    if (perspective)
        matrix.perspective(fov, aspect, zNear, zFar);
    else
        matrix.ortho(-2.0f * aspect, 2.0f * aspect, -2.0f, 2.0f, zNear, zFar);
    return matrix;
}

QMatrix4x4 Camera::getView() const {
    QMatrix4x4 matrix;
    Transform& t = gameObject().transform();
    matrix.setToIdentity();
    matrix.lookAt(t.position(), t.position() + t.rotation() * QVector3D(0.0f, 0.0f, 1.0f), t.rotation() * QVector3D(0.0f, 1.0f, 0.0f));
    return matrix;
}

void Camera::toggleView(bool p) {
    perspective = p;
}

void Camera::lookAt(QVector3D pos) {
    Transform& t = gameObject().transform();
    t.rotation() = QQuaternion::fromDirection(pos - t.position(), QVector3D(0.0f, 1.0f, 0.0f));
}

void Camera::apply(QOpenGLShaderProgram * program) {
    program->setUniformValue("m_projection", getProjection());
    program->setUniformValue("m_view", getView());
    program->setUniformValue("v_camerapos", gameObject().transform().position());
}

void Camera::destroy() {
    removeComponent();
    delete this;
}

void Camera::clone(GameObject *c) {
    Camera * cam = c->addComponent<Camera>();
    cam->perspective = perspective;
    cam->fov = fov;
    cam->zNear = zNear;
    cam->zFar = zFar;
    cam->aspect = aspect;
}
