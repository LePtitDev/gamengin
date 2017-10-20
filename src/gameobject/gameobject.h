#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"

#include <vector>
#include <string>

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class GameObject {

    friend class Component;

private:

    // GameObject parent
    GameObject * parent;

    // GameObject children
    std::vector<GameObject *> children;

    // GameObject components
    std::vector<Component *> components;

    // Inited component count
    int initedCount;

public:

    // GameObject name
    std::string name;

    // Basic constructor
    GameObject();

    // Get transform component
    Transform& transform();

    // Get transform component
    const Transform& transform() const;

    // Add a new component in the GameObject
    template <typename T>
    T * addComponent() {
        components.push_back(new T(this));
        return (T *)components.back();
    }

    // Get a component in the GameObject
    template <typename T>
    T * getComponent() {
        for (size_t i = 0, sz = components.size(); i < sz; i++) {
            if (T::isInstance(components[i]))
                return (T *)components[i];
        }
        return 0;
    }

    // Get a component in the GameObject
    template <typename T>
    const T * getComponent() const {
        for (size_t i = 0, sz = components.size(); i < sz; i++) {
            if (T::isInstance(components[i]))
                return (T *)components[i];
        }
        return 0;
    }

    // Get a component in the GameObject
    template <typename T>
    std::vector<T *> getComponents() {
        std::vector<T *> res;
        for (size_t i = 0, sz = components.size(); i < sz; i++) {
            if (T::isInstance(components[i]))
                res.push_back((T *)components[i]);
        }
        return res;
    }

    // Get a component in the GameObject
    template <typename T>
    const std::vector<T *> getComponents() const {
        std::vector<T *> res;
        for (size_t i = 0, sz = components.size(); i < sz; i++) {
            if (T::isInstance(components[i]))
                res.push_back((T *)components[i]);
        }
        return res;
    }

    // Add a GameObject
    void addChild(GameObject * g);

    // Get a child
    GameObject * getChid(unsigned int i);

    // Get a child
    const GameObject * getChid(unsigned int i) const;

    // Get children count
    unsigned int childrenCount() const;

    // Destroy a GameObject
    void destroy();

    // Clear the GameObject
    void clear();

    // Clone a GameObject
    void clone(GameObject * g);

    // Update callback
    void update();

    // Called when OpenGL rendering
    void paintGL(QOpenGLShaderProgram *program, const QMatrix4x4& matrix);

private:
    
    // Remove a child
    void removeChild(GameObject * g);

    // Remove a component
    void removeComponent(void * component);

};

#endif // GAMEOBJECT_H
