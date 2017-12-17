#include "lua.h"

#include "../assets/scene.h"
#include "../../include/lua/lua.hpp"

namespace LuaLib {

/// Load an asset
///
/// Parameters :
/// - asset name
/// - asset path
///
/// Return asset pointer if success and nil otherwise
int LoadAsset(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    Asset * asset = Asset::Load(lua_tostring(L, 1), lua_tostring(L, 2));
    if (asset == 0) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, (void *)asset);
    return 1;
}

}

void LuaScript::loadLibScene() {
    createFunction("LoadAsset", LuaLib::LoadAsset);
}
