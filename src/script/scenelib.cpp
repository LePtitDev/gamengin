#include "lua.h"
#include "../../include/lua/lua.hpp"
#include "../assets/scene.h"
#include "../geometry/shapes.h"

#include <QImage>

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

/// Create a terrain based on heightmap
///
/// Parameters:
/// - asset name
/// - heightmap path
///
/// Return asset pointer if success and nil otherwise
int CreateHeightTerrain(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    QImage heightmap(lua_tostring(L, 2));
    GeometryTerrain(lua_tostring(L, 1), heightmap);
    Asset * asset = Asset::Find(lua_tostring(L, 1));
    if (asset == 0) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, (void *)state);
    return 1;
}

/// Create a new empty prefab
///
/// Parameters :
/// - prefab name
///
/// Return asset pointer if success and nil otherwise
int CreatePrefab(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    Asset * asset = new Asset(lua_tostring(L, 1), new GameObject);

    Asset::Add(asset);
    lua_pushlightuserdata(L, (void *)asset->getData<GameObject>());
    return 1;
}

/// Find an existing prefab
///
/// Parameters :
/// - prefab name
///
/// Return asset pointer if success and nil otherwise
int FindPrefab(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    Asset * asset = Asset::Find(lua_tostring(L, 1));
    if (asset == 0 || asset->getData<GameObject>() == 0) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, (void *)asset->getData<GameObject>());
    return 1;
}

/// Load a prefab
///
/// Parameters :
/// - prefab name
/// - prefab path
///
/// Return asset pointer if success and nil otherwise
int LoadPrefab(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    Asset * asset = Asset::LoadPrefab(lua_tostring(L, 1), lua_tostring(L, 2));
    if (asset == 0 || asset->getData<GameObject>() == 0) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, (void *)asset->getData<GameObject>());
    return 1;
}

}

void LuaScript::loadLibScene() {
    createFunction("LoadAsset", LuaLib::LoadAsset);
    createFunction("CreateHeightTerrain", LuaLib::CreateHeightTerrain);
    createFunction("CreatePrefab", LuaLib::CreatePrefab);
    createFunction("FindPrefab", LuaLib::FindPrefab);
    createFunction("LoadPrefab", LuaLib::LoadPrefab);
}
