#ifndef MATERIAL_H
#define MATERIAL_H

#include "component.h"
#include "../assets/assets.h"

#include <memory>

#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

class Material : public Component {

    // Asset
    Asset * texture;

public:

    // Basic constructor
    Material(GameObject * parent);

    // Assign the texture
    bool assignTexture(const char * name);

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

    // Called when OpenGL rendering
    void paintGL(QOpenGLShaderProgram *program);

    // Return the default texture
    static std::shared_ptr<QOpenGLTexture>& defaultTexture();

};

#endif // MATERIAL_H
