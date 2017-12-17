#include "lua.h"
#include "../../include/lua/lua.hpp"
#include "../assets/assets.h"
#include "../assets/scene.h"
#include "../gameobject/gameobject.h"
#include "../gameobject/geometry.h"
#include "../gameobject/material.h"
#include "../gameobject/camera.h"
#include "../gameobject/rigidbody.h"
#include "../gameobject/particle_system.h"
#include "../controller/camera_rts.h"
#include "../controller/camera_facing.h"
#include "../geometry/mesh.h"

namespace LuaLib {

////////////////////////
////// GAMEOBJECT //////
////////////////////////

/// Add a component to an object
///
/// Parameters :
/// - asset name / gameobject pointer
/// - component name
///
/// Return asset pointer if success and nil otherwise
int GameObject_AddComponent(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    std::string comp = lua_tostring(L, 2);
    void * result = 0;
    if (comp == "Transform")
        result = (void *)gm->addComponent<Transform>();
    else if (comp == "Geometry")
        result = (void *)gm->addComponent<Geometry>();
    else if (comp == "Material")
        result = (void *)gm->addComponent<Material>();
    else if (comp == "Camera")
        result = (void *)gm->addComponent<Camera>();
    else if (comp == "CameraRTSController")
        result = (void *)gm->addComponent<CameraRTSController>();
    else if (comp == "CameraFacingController")
        result = (void *)gm->addComponent<CameraFacingController>();
    else if (comp == "Rigidbody")
        result = (void *)gm->addComponent<Rigidbody>();
    else if (comp == "ParticleSystem")
        result = (void *)gm->addComponent<ParticleSystem>();
    else {
        // AJOUTER LES SCRIPTS
    }
    if (result == 0)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L, result);
    return 1;
}

/// Get a component of an object
///
/// Parameters :
/// - asset name / gameobject pointer
/// - component name
///
/// Return asset pointer if success and nil otherwise
int GameObject_GetComponent(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    std::string comp = lua_tostring(L, 2);
    void * result = 0;
    if (comp == "Transform")
        result = (void *)gm->getComponent<Transform>();
    else if (comp == "Geometry")
        result = (void *)gm->getComponent<Geometry>();
    else if (comp == "Material")
        result = (void *)gm->getComponent<Material>();
    else if (comp == "Camera")
        result = (void *)gm->getComponent<Camera>();
    else if (comp == "RTSCameraController")
        result = (void *)gm->getComponent<CameraRTSController>();
    else if (comp == "CameraFacingController")
        result = (void *)gm->getComponent<CameraFacingController>();
    else if (comp == "Rigidbody")
        result = (void *)gm->getComponent<Rigidbody>();
    else if (comp == "ParticleSystem")
        result = (void *)gm->getComponent<ParticleSystem>();
    else {
        // AJOUTER LES SCRIPTS
    }
    if (result == 0)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L, result);
    return 1;
}

/// Instanciate a gameobject
///
/// Parameters :
/// - prefab asset name / prefab pointer
///
/// Return gameobject pointer if success and nil otherwise
int GameObject_Instanciate(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    GameObject * result = new GameObject();
    gm->clone(result);
    Scene::main->addGameObject(result);
    lua_pushlightuserdata(L, (void *)result);
    return 1;
}

/// Get gameobject position
///
/// Parameters :
/// - asset name / gameobject pointer
///
/// Return x, y, z if success and nil otherwise
int GameObject_GetPosition(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D& pos = gm->transform().position;
    lua_pushnumber(L, pos.x());
    lua_pushnumber(L, pos.y());
    lua_pushnumber(L, pos.z());
    return 3;
}

/// Get gameobject rotation
///
/// Parameters :
/// - asset name / gameobject pointer
///
/// Return x, y, z if success and nil otherwise
int GameObject_GetRotation(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QQuaternion& rot = gm->transform().rotation;
    lua_pushnumber(L, rot.x());
    lua_pushnumber(L, rot.y());
    lua_pushnumber(L, rot.z());
    return 3;
}

/// Get gameobject scale
///
/// Parameters :
/// - asset name / gameobject pointer
///
/// Return x, y, z if success and nil otherwise
int GameObject_GetScale(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D& scale = gm->transform().scale;
    lua_pushnumber(L, scale.x());
    lua_pushnumber(L, scale.y());
    lua_pushnumber(L, scale.z());
    return 3;
}

/// Set gameobject position
///
/// Parameters :
/// - asset name / gameobject pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int GameObject_SetPosition(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D& pos = gm->transform().position;
    pos.setX(lua_tonumber(L, 2));
    pos.setY(lua_tonumber(L, 3));
    pos.setZ(lua_tonumber(L, 4));
    lua_pushboolean(L, 1);
    return 1;
}

/// Set gameobject rotation
///
/// Parameters :
/// - asset name / gameobject pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int GameObject_SetRotation(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QQuaternion& rot = gm->transform().rotation;
    rot.setX(lua_tonumber(L, 2));
    rot.setY(lua_tonumber(L, 3));
    rot.setZ(lua_tonumber(L, 4));
    lua_pushboolean(L, 1);
    return 1;
}

/// Set gameobject scale
///
/// Parameters :
/// - asset name / gameobject pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int GameObject_SetScale(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>()) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D& scale = gm->transform().scale;
    scale.setX(lua_tonumber(L, 2));
    scale.setY(lua_tonumber(L, 3));
    scale.setZ(lua_tonumber(L, 4));
    lua_pushboolean(L, 1);
    return 1;
}

//////////////////////
////// GEOMETRY //////
//////////////////////

/// Assign mesh geometry
///
/// Parameters :
/// - geometry pointer
/// - mesh asset name
///
/// Return true if success and false otherwise
int Geometry_Assign(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Geometry * geometry = (Geometry *)lua_topointer(L, 1);
    if (geometry == 0 || !geometry->assignMesh(lua_tostring(L, 2)))
        lua_pushboolean(L, 0);
    else
        lua_pushboolean(L, 1);
    return 1;
}

//////////////////////
////// MATERIAL //////
//////////////////////

/// Assign texture material
///
/// Parameters :
/// - material pointer
/// - texture asset name
///
/// Return true if success and false otherwise
int Material_Assign(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Material * mat = (Material *)lua_topointer(L, 1);
    if (mat == 0 || !mat->assignTexture(lua_tostring(L, 2)))
        lua_pushboolean(L, 0);
    else
        lua_pushboolean(L, 1);
    return 1;
}

///////////////////////
////// RIGIDBODY //////
///////////////////////

/// Get rigidbody gravity
///
/// Parameters :
/// - rigidbody pointer
///
/// Return x, y, z if success and nil otherwise
int Rigidbody_GetGravity(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    Rigidbody * rb = (Rigidbody *)lua_topointer(L, 1);
    if (rb == 0)
        lua_pushnil(L);
    lua_pushnumber(L, rb->gravity.x());
    lua_pushnumber(L, rb->gravity.y());
    lua_pushnumber(L, rb->gravity.z());
    return 3;
}

/// Set rigidbody gravity
///
/// Parameters :
/// - rigidbody pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int Rigidbody_SetGravity(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Rigidbody * rb = (Rigidbody *)lua_topointer(L, 1);
    if (rb == 0)
        lua_pushboolean(L, 0);
    rb->gravity.setX(lua_tonumber(L, 2));
    rb->gravity.setY(lua_tonumber(L, 3));
    rb->gravity.setZ(lua_tonumber(L, 4));
    lua_pushboolean(L, 1);
    return 1;
}

/////////////////////////////
////// PARTICLE SYSTEM //////
/////////////////////////////

/// Assign particule emitter
///
/// Parameters :
/// - material pointer
/// - mesh asset name
///
/// Return true if success and false otherwise
int ParticleSystem_AssignEmitter(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0 || !ps->assignEmitter(lua_tostring(L, 2)))
        lua_pushboolean(L, 0);
    else
        lua_pushboolean(L, 1);
    return 1;
}

/// Assign particule prefab
///
/// Parameters :
/// - material pointer
/// - prefab asset name
///
/// Return true if success and false otherwise
int ParticleSystem_AssignParticule(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0 || !ps->assignParticle(lua_tostring(L, 2)))
        lua_pushboolean(L, 0);
    else
        lua_pushboolean(L, 1);
    return 1;
}

/// Get particule duration
///
/// Parameters :
/// - particule system pointer
///
/// Return duration if success and nil otherwise
int ParticleSystem_GetParticuleDuration(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0)
        lua_pushnil(L);
    lua_pushnumber(L, ps->ParticleDuration);
    return 1;
}

/// Get particule frequency
///
/// Parameters :
/// - particule system pointer
///
/// Return frequency if success and nil otherwise
int ParticleSystem_GetParticuleFrequency(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0)
        lua_pushnil(L);
    lua_pushnumber(L, ps->ParticleFrequency);
    return 1;
}

/// Set particule duration
///
/// Parameters :
/// - particule system pointer
/// - duration
///
/// Return true if success and false otherwise
int ParticleSystem_SetParticuleDuration(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0)
        lua_pushboolean(L, 0);
    ps->ParticleDuration = lua_tonumber(L, 2);
    lua_pushboolean(L, 1);
    return 1;
}

/// Set particule frequency
///
/// Parameters :
/// - particule system pointer
/// - frequency
///
/// Return true if success and false otherwise
int ParticleSystem_SetParticuleFrequency(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    ParticleSystem * ps = (ParticleSystem *)lua_topointer(L, 1);
    if (ps == 0)
        lua_pushboolean(L, 0);
    ps->ParticleFrequency = lua_tonumber(L, 2);
    lua_pushboolean(L, 1);
    return 1;
}

}

void LuaScript::loadLibScript() {
    lua_State * L = (lua_State *)state;

    /// GAMEOBJECT ///

    lua_createtable(L, 0, 0);
    int id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_AddComponent);
    lua_setfield(L, id, "AddComponent");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetComponent);
    lua_setfield(L, id, "GetComponent");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_Instanciate);
    lua_setfield(L, id, "Instanciate");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetPosition);
    lua_setfield(L, id, "GetPosition");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetRotation);
    lua_setfield(L, id, "GetRotation");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetScale);
    lua_setfield(L, id, "GetScale");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_SetPosition);
    lua_setfield(L, id, "SetPosition");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_SetRotation);
    lua_setfield(L, id, "SetRotation");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_SetScale);
    lua_setfield(L, id, "SetScale");
    // Méthodes de GameObject

    lua_setglobal(L, "GameObject");

    /// GEOMETRY ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Geometry_Assign);
    lua_setfield(L, id, "Assign");
    lua_setglobal(L, "Geometry");

    /// MATERIAl ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Material_Assign);
    lua_setfield(L, id, "Assign");
    lua_setglobal(L, "Material");

    /// RIGIDBODY ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Rigidbody_GetGravity);
    lua_setfield(L, id, "GetGravity");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Rigidbody_SetGravity);
    lua_setfield(L, id, "SetGravity");
    lua_setglobal(L, "Rigidbody");

    /// PARTICULE SYSTEM ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_AssignEmitter);
    lua_setfield(L, id, "AssignEmitter");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_AssignParticule);
    lua_setfield(L, id, "AssignParticle");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_GetParticuleDuration);
    lua_setfield(L, id, "GetParticleDuration");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_GetParticuleFrequency);
    lua_setfield(L, id, "GetParticleFrequency");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_SetParticuleDuration);
    lua_setfield(L, id, "SetParticleDuration");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::ParticleSystem_SetParticuleFrequency);
    lua_setfield(L, id, "SetParticleFrequency");
    lua_setglobal(L, "ParticleSystem");
}
