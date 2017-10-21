#ifndef CAMERA_H
#define CAMERA_H

#include "component.h"

#include <QMatrix4x4>

class Camera : public Component {

public:

    // MainCamera instance
    static Camera * mainCamera;

private:

    // Indicate if projection mode is perspective or orthographic
    bool perspective;

    // Field of view
    float fov;

    // Near distance
    float zNear;

    // Far distance
    float zFar;

    // Aspect ratio
    float aspect;

    // Projection matrix
    QMatrix4x4 projection;

public:

    // Public accessor to perspective
    const bool& Perspective;

    // Public accessor to fov
    const float& FOV;

    // Public accessor to near
    const float& Near;

    // Public accessor to far
    const float& Far;

    // Public accessor to aspect
    const float& Aspect;

    // Public accessor to projection
    const QMatrix4x4& Projection;

    // Basic constructor
    Camera(GameObject * parent);

    // Get current projection
    QMatrix4x4 getProjection() const;

    // Toggle to perspective or orthographic
    void toggleView();

    // Toggle to perspective or orthographic
    void toggleView(bool p);

    // Set the camera aspect
    void setFOV(float f);

    // Set the camera aspect
    void setNear(float n);

    // Set the camera aspect
    void setFar(float f);

    // Set the camera aspect
    void setAspect(float a);

    // Set camera lookat to position
    void lookAt(QVector3D pos);

    // Refresh projection
    void refresh();

    // Component override
    virtual void destroy() override;

    // Component override
    virtual int component() const override;

    // Component override
    virtual void clone(GameObject * c) override;

    // Indicate if the componant is an instance of Camera
    static bool isInstance(Component * c);

};

#endif // CAMERA_H
