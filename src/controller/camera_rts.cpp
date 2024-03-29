#include "camera_rts.h"
#include "../gameobject/gameobject.h"

#include <QtMath>

CameraRTSController::CameraRTSController(GameObject *parent) :
    Component(parent),
    wheelDelta(0),
    distance(30.0f),
    translationSpeed(0.05f),
    rotationSpeed(15.0f),
    zoomSpeed(0.1f),
    maxZoom(2.0f),
    minZoom(0.5f),
    rotation(90)
{
    zoom = maxZoom;
}

void CameraRTSController::update() {
    if (!timer.isValid()) {
        timer.start();
        gameObject().transform().setPosition(center + QVector3D(0.0f, 1.0f, 1.0f) * distance * (zoom > 0.0f ? 1.0f / (1.0f + zoom) : 1.0f - zoom));
        return;
    }
    float elapsed = (float)timer.elapsed() / 1000.0;
    for (size_t i = 0, sz = mousePressed.size(); i < sz; i++) {
        if (mousePressed[i] == Qt::RightButton)
            rotation -= (float)mouseMove.x() * rotationSpeed * elapsed;
    }
    if (wheelDelta != 0) {
        zoom += (float)wheelDelta * zoomSpeed * elapsed;
        if (zoom < minZoom)
            zoom = minZoom;
        if (zoom > maxZoom)
            zoom = maxZoom;
    }
    float rad = qDegreesToRadians(rotation);
    QVector3D forward = gameObject().transform().rotation() * QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D moving;
    forward.setY(0);
    for (size_t i = 0, sz = keyPressed.size(); i < sz; i++) {
        switch (keyPressed[i]) {
        case Qt::Key_Z:
            moving += forward;
            break;
        case Qt::Key_S:
            moving -= forward;
            break;
        case Qt::Key_Q:
            moving -= QVector3D(-forward.z(), 0.0f, forward.x());
            break;
        case Qt::Key_D:
            moving += QVector3D(-forward.z(), 0.0f, forward.x());
            break;
        }
    }
    moving.normalize();
    moving *= translationSpeed;
    center += moving;
    gameObject().transform().setPosition(center + QVector3D(-qSin(rad), (zoom >= 0.0f ? 1.0f / (1.0f + zoom) : 2.0f - 1.0f / (1.0f - zoom)), -qCos(rad)) * distance * (zoom > 0.0f ? 1.0f / (1.0f + zoom) : 1.0f - zoom));
    gameObject().transform().setRotation(QQuaternion::fromDirection(QVector3D(qSin(rad), -qDegreesToRadians(45.0f) * (zoom >= 0.0f ? 1.0f / (1.0f + zoom) : 2.0f - 1.0f / (1.0f - zoom)), qCos(rad)), QVector3D(0.0f, 1.0f, 0.0f)));
    timer.restart();
    wheelDelta = 0;
    mouseMove = QPoint();
}

void CameraRTSController::keyPressEvent(QKeyEvent * event) {
    keyPressed.push_back(event->key());
}

void CameraRTSController::keyReleaseEvent(QKeyEvent * event) {
    for (size_t i = 0, sz = keyPressed.size(); i < sz; i++) {
        if (keyPressed[i] == event->key()) {
            keyPressed.erase(keyPressed.begin() + i);
            break;
        }
    }
}

void CameraRTSController::mousePressEvent(QMouseEvent * event) {
    mousePressed.push_back(event->button());
    lastPos = event->pos();
}

void CameraRTSController::mouseReleaseEvent(QMouseEvent * event) {
    for (size_t i = 0, sz = mousePressed.size(); i < sz; i++) {
        if (mousePressed[i] == event->button()) {
            mousePressed.erase(mousePressed.begin() + i);
            break;
        }
    }
}

void CameraRTSController::mouseMoveEvent(QMouseEvent * event) {
    mouseMove += (event->pos() - lastPos);
    lastPos = event->pos();
}

void CameraRTSController::wheelEvent(QWheelEvent * event) {
    wheelDelta += event->delta();
}

void CameraRTSController::destroy() {
    removeComponent();
    delete this;
}

void CameraRTSController::clone(GameObject *c) {
    CameraRTSController * cam = c->addComponent<CameraRTSController>();
    cam->timer = timer;
    cam->keyPressed = keyPressed;
    cam->mousePressed = mousePressed;
    cam->lastPos = lastPos;
    cam->mouseMove = mouseMove;
    cam->wheelDelta = wheelDelta;
    cam->center = center;
    cam->distance = distance;
    cam->translationSpeed = translationSpeed;
    cam->rotationSpeed = rotationSpeed;
    cam->zoomSpeed = zoomSpeed;
    cam->maxZoom = maxZoom;
    cam->minZoom = minZoom;
    cam->rotation = rotation;
    cam->zoom = zoom;
}
