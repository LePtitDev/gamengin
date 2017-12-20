#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

#include <QVector3D>
#include <QQuaternion>

class GameObject;

class Transform : public Component {

public:

    // GameObject local position
    QVector3D localPosition;

    // GameObject local rotation
    QQuaternion localRotation;

    // GameObject local scale
    QVector3D localScale;

    // GameObject position
    QVector3D position() const;

    // GameObject rotation
    QQuaternion rotation() const;

    // GameObject scale
    QVector3D scale() const;

    // Set position
    void setPosition(const QVector3D&);

    // Set rotation
    void setRotation(const QQuaternion&);

    // Set scale
    void setScale(const QVector3D&);

    // Basic constructor
    Transform(GameObject * parent);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // TRANSFORM_H
