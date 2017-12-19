#ifndef CAMERA_H
#define CAMERA_H

#include "component.h"
#include "../geometry/ray.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class Camera : public Component {

public:

    // MainCamera instance
    static Camera * mainCamera;

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

    // Basic constructor
    Camera(GameObject * parent);

    // Get ray camera by screen coordinates
    Ray getRay(int x, int y) const;

    // Toggle to perspective or orthographic
    void toggleView();

    // Get projection matrix
    QMatrix4x4 getProjection() const;

    // Get view matrix
    QMatrix4x4 getView() const;

    // Toggle to perspective or orthographic
    void toggleView(bool p);

    // Set camera lookat to position
    void lookAt(QVector3D pos);

    // Assign projection and view matrix
    void apply(QOpenGLShaderProgram * program);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // CAMERA_H
