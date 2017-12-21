#ifndef SCRIPT_H
#define SCRIPT_H

#include "component.h"
#include "../script/lua.h"

class GameObject;

class ScriptComponent : public Component {

    // LUA Script name
    std::string scriptName;

    // Indicate if script was started
    bool started;

public:

    // LUA Script
    LuaScript script;

    // Basic constructor
    ScriptComponent(GameObject * parent);

    // Get script name
    const char * getScriptName() const;

    // Assign script
    bool assign(const char * name);

    // Update callback
    virtual void update() override;

    // Key press event callback
    virtual void keyPressEvent(QKeyEvent * event) override;

    // Key release event callback
    virtual void keyReleaseEvent(QKeyEvent * event) override;

    // Mouse press event callback
    virtual void mousePressEvent(QMouseEvent * event) override;

    // Mouse release event callback
    virtual void mouseReleaseEvent(QMouseEvent * event) override;

    // Mouse move event callback
    virtual void mouseMoveEvent(QMouseEvent * event) override;

    // Mouse wheel event callback
    virtual void wheelEvent(QWheelEvent * event) override;

    // Component override
    virtual void destroy() override;

    // Component override
    virtual void clone(GameObject * c) override;

};

#endif // TRANSFORM_H
