#include "material.h"
#include "gameobject.h"

Material::Material(GameObject *parent) :
    Component(parent), texture(0)
{

}

bool Material::assignTexture(const char *name) {
    Asset * asset = Asset::Find(name);
    if (asset == 0)
        return false;
    texture = asset;
    return true;
}

void Material::destroy() {
    removeComponent();
    delete this;
}

void Material::clone(GameObject *c) {
    Material * mat = c->addComponent<Material>();
    if (texture != 0)
        mat->texture = texture;
}

void Material::paintGL(QOpenGLShaderProgram *program) {
    if (texture != 0)
        texture->getData<QOpenGLTexture>()->bind();
    else
        defaultTexture()->bind();

    // Assigne la texture dans le fragment shader
    program->setUniformValue("texture", 0);
}

std::shared_ptr<QOpenGLTexture>& Material::defaultTexture() {
    // Charge la texture par défaut
    static std::shared_ptr<QOpenGLTexture> texture(new QOpenGLTexture(QImage("./res/default.png").mirrored()));

    // Assigne le mode de filtrage pour la minification de la texture en "plus proche voisin"
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Assigne le mode de filtrage pour la magnification de la texture en "linéaire"
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Définie la texture comme étant répétitive
    texture->setWrapMode(QOpenGLTexture::Repeat);

    return texture;
}
