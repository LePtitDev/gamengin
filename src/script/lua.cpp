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

LuaScript::Variable LuaScript::getVariable(const char *name) {
    lua_settop((lua_State *)state, 0);
    lua_getglobal((lua_State *)state, name);
    Variable var = getVariable(1);
    lua_pop((lua_State *)state, 1);
    return var;
}

LuaScript::Variable LuaScript::getVariable(int luaID) {
    Variable var;
    switch (lua_type((lua_State *)state, luaID)) {
    case LUA_TNIL:
        var.type = NIL;
        break;
    case LUA_TBOOLEAN:
        var.type = BOOLEAN;
        var.v_boolean = (bool)(lua_toboolean((lua_State *)state, luaID) != 0);
        break;
    case LUA_TNUMBER:
        var.type = NUMBER;
        var.v_number = (float)lua_tonumber((lua_State *)state, luaID);
        break;
    case LUA_TSTRING:
        var.type = STRING;
        var.v_string = lua_tostring((lua_State *)state, luaID);
        break;
    case LUA_TTABLE:
        var.type = TABLE;
        break;
    case LUA_TFUNCTION:
        var.type = FUNCTION;
        var.v_pointer = (void *)lua_tocfunction((lua_State *)state, luaID);
        break;
    case LUA_TLIGHTUSERDATA:
        var.type = POINTER;
        var.v_pointer = (void *)lua_topointer((lua_State *)state, luaID);
        break;
    default:
        var.type = UNKNOW;
    }
    return var;
}

void LuaScript::pushVariable(const Variable &var) {
    switch (var.type) {
    case NIL:
        lua_pushnil((lua_State *)state);
        break;
    case BOOLEAN:
        lua_pushboolean((lua_State *)state, var.v_boolean ? 1 : 0);
        break;
    case NUMBER:
        lua_pushnumber((lua_State *)state, var.v_number);
        break;
    case STRING:
        lua_pushstring((lua_State *)state, var.v_string.c_str());
        break;
    case POINTER:
        lua_pushlightuserdata((lua_State *)state, var.v_pointer);
        break;
    default:
        lua_pushnil((lua_State *)state);
    }
}

void LuaScript::createVariable(const char *name, const Variable &var) {
    pushVariable(var);
    lua_setglobal((lua_State *)state, name);
}

void LuaScript::createFunction(const char *name, int (*value)(void *)) {
    lua_register((lua_State *)state, name, (int(*)(lua_State *))value);
}

LuaScript::Variable LuaScript::callFunction(const char *name, Variable *args, int count) {
    Variable result;
    lua_getglobal((lua_State *)state, name);
    if (!lua_isfunction((lua_State *)state, -1)) {
        lua_pop((lua_State *)state, 1);
        result.type = VariableType::UNKNOW;
        return result;
    }
    else {
        for (int i = 0; i < count; i++)
            pushVariable(args[i]);
        lua_call((lua_State *)state, count, 1);
        return getVariable(-1);
    }
}
