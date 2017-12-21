#include "transform.h"
#include "gameobject.h"

Transform::Transform(GameObject *parent) :
    Component(parent),
    localScale(1.0f, 1.0f, 1.0f)
{

}

QVector3D Transform::position() const {
    GameObject * parent = gameObject().getParent();
    if (parent != 0)
        return parent->transform().rotation() * localPosition + parent->transform().position();
    return localPosition;
}

QQuaternion Transform::rotation() const {
    GameObject * parent = gameObject().getParent();
    if (parent != 0) {
        float sx, sy, sz; localRotation.getEulerAngles(&sx, &sy, &sz);
        QQuaternion rt = parent->transform().rotation();
        float rx, ry, rz; rt.getEulerAngles(&rx, &ry, &rz);
        return QQuaternion::fromEulerAngles(sx + rx, sy + ry, sz + rz);
    }
    return localRotation;
}

QVector3D Transform::scale() const {
    GameObject * parent = gameObject().getParent();
    if (parent != 0)
        return localScale * parent->transform().scale();
    return localScale;
}

void Transform::setPosition(const QVector3D& pos) {
    GameObject * parent = gameObject().getParent();
    if (parent != 0)
        localPosition = pos - parent->transform().position();
    else
        localPosition = pos;
}

void Transform::setRotation(const QQuaternion& rot) {
    GameObject * parent = gameObject().getParent();
    if (parent != 0) {
        float sx, sy, sz; rot.getEulerAngles(&sx, &sy, &sz);
        QQuaternion rt = parent->transform().rotation();
        float rx, ry, rz; rt.getEulerAngles(&rx, &ry, &rz);
        localRotation = QQuaternion::fromEulerAngles(sx - rx, sy - ry, sz - rz);
    }
    else
        localRotation = rot;
}

void Transform::setScale(const QVector3D& sca) {
    GameObject * parent = gameObject().getParent();
    if (parent != 0)
        localScale = sca / parent->transform().scale();
    else
        localScale = sca;
}

void Transform::destroy() {
    removeComponent();
    delete this;
}

void Transform::clone(GameObject * c) {
    Transform * t = c->addComponent<Transform>();
    t->localPosition = localPosition;
    t->localRotation = localRotation;
    t->localScale = localScale;
}
