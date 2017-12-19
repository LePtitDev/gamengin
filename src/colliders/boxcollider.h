#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../gameobject/collider.h"

class BoxCollider : public Collider {

public:

    // Box offset and size
    QVector3D offset, size;

    // Basic constructor
    BoxCollider(GameObject * parent) : Collider(parent) {}

    // Get bounds
    virtual Bounds bounds() const {
        Transform& transform = gameObject().transform();
        Bounds result;
        result.center = transform.position + transform.rotation * offset;
        QVector3D halfSize = size * 0.5f;
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(), -halfSize.y(), -halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(), -halfSize.y(),  halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(),  halfSize.y(), -halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(),  halfSize.y(),  halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D( halfSize.x(), -halfSize.y(), -halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D( halfSize.x(), -halfSize.y(),  halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D( halfSize.x(),  halfSize.y(), -halfSize.z())));
        result.encapsulate(transform.position + transform.rotation * (offset - QVector3D( halfSize.x(),  halfSize.y(),  halfSize.z())));
        return result;
    }

    // Does ray intersect this ?
    virtual bool intersectRay(const Ray& ray, float& distance) const;

    // Component override
    virtual void destroy() override {
        removeComponent();
        delete this;
    }

    // Component override
    virtual void clone(GameObject * g) override {
        BoxCollider * c = g->addComponent<BoxCollider>();
        c->offset = offset;
        c->size = size;
    }

};

#endif // BOXCOLLIDER_H
