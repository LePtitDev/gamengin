#include "lua.h"

#include "../assets/game.h"
#include "../../include/lua/lua.hpp"

namespace LuaLib {

int CreateScene(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushlightuserdata(L, (void *)0);
        return 1;
    }
    SceneManager * scene = new SceneManager(lua_tostring(L, 1), lua_tostring(L, 2));
    SceneManager::GetScenes().push_back(scene);
    lua_pushlightuserdata(L, (void *)scene);
    return 1;
}

int SetDefaultScene(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushboolean(L, 0);
        return 1;
    }
    SceneManager * scene = 0;
    if (lua_isstring(L, 1))
        scene = SceneManager::Find(lua_tostring(L, 1));
    else if (lua_isuserdata(L, 1))
        scene = (SceneManager *)lua_touserdata(L, 1);
    if (scene != 0)
        scene->load();
    lua_pushboolean(L, scene != 0 ? 1 : 0);
    return 1;
}

}

void LuaScript::loadLibGame() {
    createFunction("CreateScene", LuaLib::CreateScene);
    createFunction("SetDefaultScene", LuaLib::SetDefaultScene);
}
