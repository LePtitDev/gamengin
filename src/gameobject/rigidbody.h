#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "component.h"

#include <QVector3D>
#include <QElapsedTimer>

class Rigidbody : public Component {

    // Elapsed timer
    QElapsedTimer timer;

public:

    // Gravity force
    QVector3D gravity;

    // Velocity force
    QVector3D velocity;

    // Basic constructor
    Rigidbody(GameObject * parent);

    // Update callback
    virtual void update() override;

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // RIGIDBODY_H
