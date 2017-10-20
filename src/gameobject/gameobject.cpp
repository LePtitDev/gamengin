#include "gameobject.h"
#include "geometry.h"

GameObject::GameObject() :
    name("GameObject")
{
    addComponent<Transform>();
}

Transform& GameObject::transform() {
    return *getComponent<Transform>();
}

const Transform& GameObject::transform() const {
    return *getComponent<Transform>();
}

void GameObject::removeComponent(void *component) {
    for (size_t i = 1, sz = components.size(); i < sz; i++) {
        if (component == (void *)components[i]) {
            components.erase(components.begin() + i);
            break;
        }
    }
}

void GameObject::clear() {
    while (components.size() > 0)
        components[0]->destroy();
}

void GameObject::clone(GameObject * g) {
    g->clear();
    for (size_t i = 0, sz = components.size(); i < sz; i++)
        components[i]->clone(g);
    g->name = name;
    g->name += "(Clone)";
}

void GameObject::paintGL(QOpenGLShaderProgram *program, const QMatrix4x4& matrix) {
    Geometry * geometry = getComponent<Geometry>();
    if (geometry != 0) {
        Transform * transform = getComponent<Transform>();
        QMatrix4x4 projection(matrix);
        projection.translate(transform->position);
        projection.rotate(transform->rotation);
        projection.scale(transform->scale);
        program->setUniformValue("m_projection", projection);

        geometry->draw(program);
    }
}
