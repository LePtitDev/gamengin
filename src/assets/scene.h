#ifndef SCENE_H
#define SCENE_H

#include "assets.h"
#include "../script/lua.h"
#include "../gameobject/gameobject.h"

#include <vector>

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

    // Create and load a scene
    Scene(const char * name, const char * filename) {
        Asset * asset = Asset::Load(name, filename);
        if (asset == 0)
            return;
        Scene::main = this;
        LuaScript script;
        script.loadLibScene();
        script.load(asset->getData<std::string>()->c_str());
        script.execute();
    }

    // Get name
    const char * getName() const { return name.c_str(); }

    // Get loaded scenes
    static std::vector<Scene *>& GetScenes() {
        static std::vector<Scene *> scenes;
        return scenes;
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
