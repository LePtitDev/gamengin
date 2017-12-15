#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "../script/lua.h"

#include <vector>

class SceneManager {

    // Scene name
    std::string name;

    // Scene path
    std::string path;

public:

    // Basic constructor
    SceneManager(const char * name, const char * path) :
        name(name), path(path) {}

    // Get name
    const char * getName() const { return name.c_str(); }

    // Get path
    const char * getPath() const { return path.c_str(); }

    // Load the scene
    void load() {
        Scene::GetScenes().push_back(new Scene(name.c_str(), path.c_str()));
    }

    // Get all scenes
    static std::vector<SceneManager *>& GetScenes() {
        static std::vector<SceneManager *> scenes;
        return scenes;
    }

    // Find a scene
    static SceneManager * Find(const char * name) {
        for (auto sc : GetScenes()) {
            if (sc->name == name)
                return sc;
        }
        return 0;
    }

};

#endif // GAME_H
