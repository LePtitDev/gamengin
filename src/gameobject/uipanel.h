#ifndef UIPANEL_H
#define UIPANEL_H

#include "component.h"

#include <QVector3D>
#include <QQuaternion>

class GameObject;

class UIPanel : public Component {

public:

    // Panel position
    QVector2D position;

    // Basic constructor
    UIPanel(GameObject * parent);

    // Update callback
    virtual void update() override;

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // UIPANEL_H
