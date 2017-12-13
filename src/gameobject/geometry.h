#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "component.h"
#include "../geometry/mesh.h"
#include "../assets/assets.h"

#include <QOpenGLShaderProgram>

class Geometry : public Component {

    // Mesh asset
    Asset * mesh;

public:

    // Basic constructor
    Geometry(GameObject * parent);

    // Assign mesh
    bool assignMesh(const char * name);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

    // Draw the mesh when rendering
    virtual void draw(QOpenGLShaderProgram *program);

};

#endif // GEOMETRY_H
