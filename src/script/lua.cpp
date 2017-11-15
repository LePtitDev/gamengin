#include "lua.h"

#include "../../include/lua/lua.hpp"

LuaScript::LuaScript() : need_close(true) {
    state = (void *)luaL_newstate();
    luaL_openlibs((lua_State *)state);
}

LuaScript::LuaScript(void *s) : state(s), need_close(false) {}

LuaScript::~LuaScript() {
    if (need_close)
        lua_close((lua_State *)state);
}

bool LuaScript::load(const char * code) {
    return luaL_loadstring((lua_State *)state, code) == LUA_OK;
}

bool LuaScript::execute() {
    return lua_pcall((lua_State *)state, 0, LUA_MULTRET, 0) == LUA_OK;
}

const char * LuaScript::getError() {
    return lua_tostring((lua_State *)state, -1);
}

LuaScript::VariableType LuaScript::getType(const char *name) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    VariableType type;
    switch (lua_type((lua_State *)state, 1)) {
    case LUA_TNIL:
        type = NIL;
        break;
    case LUA_TBOOLEAN:
        type = BOOLEAN;
        break;
    case LUA_TNUMBER:
        type = NUMBER;
        break;
    case LUA_TSTRING:
        type = STRING;
        break;
    case LUA_TTABLE:
        type = TABLE;
        break;
    case LUA_TFUNCTION:
        type = FUNCTION;
        break;
    default:
        type = UNKNOW;
    }
    lua_pop((lua_State *)state,1);
    return type;
}

bool LuaScript::getVariable(const char *name, bool &value) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    bool success = false;
    if (lua_isboolean((lua_State *)state, 1)) {
        success = true;
        value = (bool)(lua_toboolean((lua_State *)state, 1) != 0);
    }
    lua_pop((lua_State *)state,1);
    return success;
}

bool LuaScript::getVariable(const char *name, int &value) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    bool success = false;
    if (lua_isinteger((lua_State *)state, 1)) {
        success = true;
        value = (int)lua_tointeger((lua_State *)state, 1);
    }
    lua_pop((lua_State *)state,1);
    return success;
}

bool LuaScript::getVariable(const char *name, float &value) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    bool success = false;
    if (lua_isnumber((lua_State *)state, 1)) {
        success = true;
        value = (float)lua_tonumber((lua_State *)state, 1);
    }
    lua_pop((lua_State *)state,1);
    return success;
}

bool LuaScript::getVariable(const char *name, std::string &value) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    bool success = false;
    if (lua_isstring((lua_State *)state, 1)) {
        success = true;
        value.clear();
        value = lua_tostring((lua_State *)state, 1);
    }
    lua_pop((lua_State *)state,1);
    return success;
}

void LuaScript::createFunction(const char *name, int (*value)(void *)) {
    lua_register((lua_State *)state, name, (int(*)(lua_State *))value);
}
