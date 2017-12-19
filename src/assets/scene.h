#ifndef SCENE_H
#define SCENE_H

#include "assets.h"
#include "../script/lua.h"
#include "../gameobject/gameobject.h"
#include "../geometry/shapes.h"

#include <vector>
#include <QOpenGLShaderProgram>

class Scene {

public:

    // Main scene
    static Scene * main;

private:

    // Scene name
    std::string name;

    // GameObjects hierarchy
    std::vector<GameObject *> objects;

public:

    // Scene width and height
    static int width, height;

    // Create and load a scene
    Scene(const char * name, const char * filename) {
        Asset * asset = Asset::Load(name, filename);
        if (asset == 0)
            return;
        Scene::main = this;
        GeometryCube("geometry:cube");
        GeometryPlane("geometry:plane");
        GeometryUIPlane("geometry:ui-plane");
        LuaScript script;
        script.loadLibScene();
        script.loadLibScript();
        script.load(asset->getData<std::string>()->c_str());
        script.execute();
    }

    // Destructor
    ~Scene() {
        for (auto it : objects)
            delete it;
    }

    // Get name
    const char * getName() const { return name.c_str(); }

    // Add a neww gameobject
    void addGameObject(GameObject * gm) {
        objects.push_back(gm);
    }

    // Find a gameobject on top of hierarchy
    GameObject * findGameObject(const char * name) {
        for (auto gm : objects) {
            if (gm->name == name)
                return gm;
        }
        return 0;
    }

    // Update gameobjects
    void update() {
        for (auto gm : objects)
            gm->update();
    }

    // Event callback
    void keyPressEvent(QKeyEvent * event) {
        for (auto gm : objects)
            gm->keyPressEvent(event);
    }

    // Event callback
    void keyReleaseEvent(QKeyEvent * event) {
        for (auto gm : objects)
            gm->keyReleaseEvent(event);
    }

    // Event callback
    void mousePressEvent(QMouseEvent * event) {
        for (auto gm : objects)
            gm->mousePressEvent(event);
    }

    // Event callback
    void mouseReleaseEvent(QMouseEvent * event) {
        for (auto gm : objects)
            gm->mouseReleaseEvent(event);
    }

    // Event callback
    void mouseMoveEvent(QMouseEvent * event) {
        for (auto gm : objects)
            gm->mouseMoveEvent(event);
    }

    // Event callback
    void wheelEvent(QWheelEvent * event) {
        for (auto gm : objects)
            gm->wheelEvent(event);
    }

    // Paint gameobjects
    void paintGL(QOpenGLShaderProgram * program) {
        for (auto gm : objects)
            gm->paintGL(program);
    }

    // Get loaded scenes
    static std::vector<Scene *>& GetScenes() {
        static std::vector<Scene *> scenes;
        return scenes;
    }

    // Clear scenes
    static void ClearScenes() {
        for (auto it : GetScenes())
            delete it;
        GetScenes().clear();
    }

    // Find a scene
    static Scene * Find(const char * name) {
        for (auto sc : GetScenes()) {
            if (sc->name == name)
                return sc;
        }
        return 0;
    }

};

#endif // SCENE_H
