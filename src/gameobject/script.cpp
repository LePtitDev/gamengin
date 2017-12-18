#include "script.h"
#include "gameobject.h"
#include "../assets/assets.h"

ScriptComponent::ScriptComponent(GameObject *parent) :
    Component(parent)
{
    script.loadLibScript();
}

const char * ScriptComponent::getScriptName() const {
    return scriptName.c_str();
}

bool ScriptComponent::assign(const char * name) {
    Asset * asset = Asset::Find(name);
    if (asset == 0 || asset->getData<std::string>() == 0)
        return false;
    scriptName = name;
    script.load(asset->getData<std::string>()->c_str());
    LuaScript::Variable vr;
    vr.type = LuaScript::VariableType::POINTER;
    vr.v_pointer = (void *)&gameObject();
    script.createVariable("this", vr);
    script.execute();
    return true;
}

void ScriptComponent::update() {
    if (script.getVariable("update").type == LuaScript::VariableType::FUNCTION)
        script.callFunction("update", 0, 0);
}

void ScriptComponent::keyPressEvent(QKeyEvent * event) {
    if (script.getVariable("keyPress").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable key;
        key.type = LuaScript::INTEGER;
        key.v_integer = event->key();
        script.callFunction("keyPress", &key, 1);
    }
}

void ScriptComponent::keyReleaseEvent(QKeyEvent * event) {
    if (script.getVariable("keyRelease").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable key;
        key.type = LuaScript::INTEGER;
        key.v_integer = event->key();
        script.callFunction("keyRelease", &key, 1);
    }
}

void ScriptComponent::mousePressEvent(QMouseEvent * event) {
    if (script.getVariable("mousePress").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable args[3];
        args[0].type = LuaScript::INTEGER;
        args[0].v_integer = (int)event->button();
        args[1].type = LuaScript::INTEGER;
        args[1].v_integer = (int)event->x();
        args[2].type = LuaScript::INTEGER;
        args[2].v_integer = (int)event->y();
        script.callFunction("mousePress", args, 3);
    }
}

void ScriptComponent::mouseReleaseEvent(QMouseEvent * event) {
    if (script.getVariable("mouseRelease").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable args[3];
        args[0].type = LuaScript::INTEGER;
        args[0].v_integer = (int)event->button();
        args[1].type = LuaScript::INTEGER;
        args[1].v_integer = (int)event->x();
        args[2].type = LuaScript::INTEGER;
        args[2].v_integer = (int)event->y();
        script.callFunction("mouseRelease", args, 3);
    }
}

void ScriptComponent::mouseMoveEvent(QMouseEvent * event) {
    if (script.getVariable("mouseMove").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable args[2];
        args[0].type = LuaScript::INTEGER;
        args[0].v_integer = (int)event->x();
        args[1].type = LuaScript::INTEGER;
        args[1].v_integer = (int)event->y();
        script.callFunction("mouseMove", args, 2);
    }
}

void ScriptComponent::wheelEvent(QWheelEvent * event) {
    if (script.getVariable("wheel").type == LuaScript::VariableType::FUNCTION) {
        LuaScript::Variable arg;
        arg.type = LuaScript::INTEGER;
        arg.v_integer = event->delta();
        script.callFunction("wheel", &arg, 1);
    }
}

void ScriptComponent::destroy() {
    removeComponent();
    delete this;
}

void ScriptComponent::clone(GameObject * c) {
    ScriptComponent * s = c->addComponent<ScriptComponent>();
    if (scriptName != "")
        s->assign(scriptName.c_str());
}
