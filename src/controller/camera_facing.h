#ifndef CAMERA_FACING_H
#define CAMERA_FACING_H

#include "../gameobject/component.h"

class CameraFacingController : public Component {

public:

    // Basic constructor
    CameraFacingController(GameObject * parent);

    // Update callback
    virtual void update() override;

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // CAMERA_FACING_H
