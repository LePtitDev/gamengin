#include "gameobject.h"
#include "geometry.h"

GameObject::GameObject() :
    name("GameObject"),
    parent(0),
    initedCount(0)
{
    addComponent<Transform>();
}

Transform& GameObject::transform() {
    return *getComponent<Transform>();
}

const Transform& GameObject::transform() const {
    return *getComponent<Transform>();
}

void GameObject::addChild(GameObject * g) {
    if (g->parent != 0)
        g->parent->removeChild(g);
    children.push_back(g);
    g->parent = this;
}

GameObject * GameObject::getChid(unsigned int i) {
    return children[i];
}

const GameObject * GameObject::getChid(unsigned int i) const {
    return children[i];
}

unsigned int GameObject::childrenCount() const {
    return (unsigned int)children.size();
}

void GameObject::destroy() {
    clear();
    if (parent != 0)
        parent->removeChild(this);
    delete this;
}

void GameObject::clear() {
    while (components.size() > 1)
        components[1]->destroy();
    if (components.size() > 0) {
        components[0]->destroy();
        components.pop_back();
    }
    while (children.size() > 0)
        children[0]->destroy();
}

void GameObject::clone(GameObject * g) {
    g->clear();
    for (size_t i = 0, sz = components.size(); i < sz; i++)
        components[i]->clone(g);
    for (size_t i = 0, sz = children.size(); i < sz; i++) {
        GameObject * o = new GameObject();
        g->addChild(o);
        children[i]->clone(o);
    }
    g->name = name;
    g->name += "(Clone)";
}

void GameObject::update() {
    if (components.size() == 0)
        return;
    std::vector<Component *> tmp_l(components);
    for (size_t i = 0, sz_i = tmp_l.size(); i < sz_i; i++) {
        for (size_t j = 0, sz_j = components.size(); j < sz_j; j++) {
            if (tmp_l[i] == components[j]) {
                tmp_l[i]->update();
                break;
            }
        }
    }
    for (size_t i = 0, sz = children.size(); i < sz; i++)
        children[i]->update();
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
    for (size_t i = 0, sz = children.size(); i < sz; i++)
        children[i]->paintGL(program, matrix);
}

void GameObject::removeChild(GameObject * g) {
    for (size_t i = 0, sz = children.size(); i < sz; i++) {
        if (g == children[i]) {
            children.erase(children.begin() + i);
            break;
        }
    }
}

void GameObject::removeComponent(void *component) {
    for (size_t i = 1, sz = components.size(); i < sz; i++) {
        if (component == (void *)components[i]) {
            components.erase(components.begin() + i);
            break;
        }
    }
}
