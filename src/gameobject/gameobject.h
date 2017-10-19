#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"

#include <vector>

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class GameObject {

    friend class Component;

private:

    // GameObject components
    std::vector<Component *> components;

public:

    // Basic constructor
    GameObject();

    // Get transform component
    Transform& transform();

    // Get transform component
    const Transform& transform() const;

    // Add a new component in the GameObject
    template <typename T>
    void addComponent() {
        components.push_back(new T(this));
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

    // Called when OpenGL rendering
    void paintGL(QOpenGLShaderProgram *program, const QMatrix4x4& matrix);

private:

    // Remove a component
    void removeComponent(void * component);

};

#endif // GAMEOBJECT_H
