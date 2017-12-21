#include "lua.h"
#include "../../include/lua/lua.hpp"
#include "../assets/assets.h"
#include "../assets/scene.h"
#include "../gameobject/gameobject.h"
#include "../gameobject/geometry.h"
#include "../gameobject/material.h"
#include "../gameobject/camera.h"
#include "../gameobject/rigidbody.h"
#include "../colliders/boxcollider.h"
#include "../gameobject/particle_system.h"
#include "../gameobject/script.h"
#include "../controller/camera_rts.h"
#include "../controller/camera_facing.h"
#include "../geometry/mesh.h"
#include "../gameobject/uipanel.h"

#include <sstream>
#include <QTime>

namespace LuaLib {

/// Print variables
int Print(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    std::stringstream ss;
    for (int i = 1; i <= argc; i++) {
        switch (lua_type(L, i)) {
            case LUA_TNIL:
                ss << "nil";
                break;
            case LUA_TBOOLEAN:
                ss << (lua_toboolean((lua_State *)state, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                ss << (float)lua_tonumber((lua_State *)state, i);
                break;
            case LUA_TSTRING:
                ss << "\"" << lua_tostring((lua_State *)state, i) << "\"";
                break;
            case LUA_TTABLE:
                ss << "array";
                break;
            case LUA_TFUNCTION:
                ss << "function";
                break;
            case LUA_TLIGHTUSERDATA:
                ss << (void *)lua_topointer((lua_State *)state, i);
                break;
            default:
                ss << "unknow";
        }
        if (i < argc)
            ss << " ";
    }
    qInfo() << ss.str().c_str();
    return 0;
}

/// Split a string
int Split(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    std::string str = lua_tostring(L, 1);
    char sep = ' ';
    if (argc > 1)
        sep = lua_tostring(L, 2)[0];
    std::string elem;
    int k = 0;
    for (unsigned int i = 0, sz = (unsigned int)str.size(); i < sz; i++) {
        if (str[i] != sep)
            elem += str[i];
        else {
            k++;
            lua_pushstring(L, elem.c_str());
            elem.clear();
        }
    }
    lua_pushstring(L, elem.c_str());
    return k + 1;
}

/// Get a prefab by name
///
/// Parameters :
/// - prefab asset name
///
/// Return prefab pointer if success and nil otherwise
int GetPrefab(void * state) {
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
    GameObject * prefab = asset->getData<GameObject>();
    if (prefab != 0)
        lua_pushlightuserdata(L, (void *)prefab);
    else
        lua_pushnil(L);
    return 1;
}

/// Get time in seconds
int GetTime(void * state) {
    lua_pushnumber((lua_State *)state, (float)Scene::startedTime.msecsTo(QTime::currentTime()) * 0.001f);
    return 1;
}

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
    else if (comp == "BoxCollider")
        result = (void *)gm->addComponent<BoxCollider>();
    else if (comp == "ParticleSystem")
        result = (void *)gm->addComponent<ParticleSystem>();
    else if (comp == "UIPanel")
        result = (void *)gm->addComponent<UIPanel>();
    else if (comp == "Script")
        result = (void *)gm->addComponent<ScriptComponent>();
    else {
        Asset * scpt = Asset::Find(comp.c_str());
        if (scpt == 0 || scpt->getData<std::string>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        result = (void *)gm->addComponent<ScriptComponent>();
        if (((ScriptComponent *)result)->assign(comp.c_str())) {
            lua_pushnil(L);
            return 1;
        }
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
    else if (comp == "BoxCollider")
        result = (void *)gm->getComponent<BoxCollider>();
    else if (comp == "ParticleSystem")
        result = (void *)gm->getComponent<ParticleSystem>();
    else if (comp == "UIPanel")
        result = (void *)gm->getComponent<UIPanel>();
    else if (comp == "Script")
        result = (void *)gm->getComponent<ScriptComponent>();
    else {
        for (auto scpt : gm->getComponents<ScriptComponent>()) {
            if (scpt->getScriptName() == comp) {
                result = (void *)scpt;
                break;
            }
        }
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
/// - parent gameobject pointer (optional)
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    GameObject * result = new GameObject();
    gm->clone(result);
    if (argc < 2)
        Scene::main->addGameObject(result);
    else
        ((GameObject *)lua_topointer(L, 2))->addChild(result);
    lua_pushlightuserdata(L, (void *)result);
    return 1;
}

/// Copy a gameobject
///
/// Parameters :
/// - gameobject pointer to assign
/// - gameobject pointer to copy
///
/// Return true if success and false otherwise
int GameObject_Copy(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    GameObject * gm_src = (GameObject *)lua_topointer(L, 1);
    GameObject * gm_dest = (GameObject *)lua_topointer(L, 2);
    gm_dest->clone(gm_src);
    lua_pushboolean(L, 1);
    return 1;
}

/// Find a gameobject on scene root
///
/// Parameters :
/// - gameobject name
///
/// Return gameobject pointer if success and nil otherwise
int GameObject_Find(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = Scene::main->findGameObject(lua_tostring(L, 1));
    if (gm == 0)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L, (void *)gm);
    return 1;
}

/// Add a child in a gameobject
///
/// Parameters :
/// - gameobject pointer
/// - gameobject child pointer / gameobject name
///
/// Return gameobject child pointer if success and nil otherwise
int GameObject_AddChild(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = (GameObject *)lua_topointer(L, 1);
    if (gm == 0) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * result = 0;
    if (lua_type(L, 2) == LUA_TSTRING) {
        result = new GameObject();
        result->name = lua_tostring(L, 2);
        gm->addChild(result);
    }
    else {
        result = (GameObject *)lua_topointer(L, 2);
        gm->addChild(result);
    }
    lua_pushlightuserdata(L, (void *)result);
    return 1;
}

/// Get a child in a gameobject
///
/// Parameters :
/// - gameobject pointer
/// - gameobject name
///
/// Return gameobject child pointer if success and nil otherwise
int GameObject_GetChild(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = (GameObject *)lua_topointer(L, 1);
    if (gm == 0) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * result = gm->getChild(lua_tostring(L, 2));
    lua_pushlightuserdata(L, (void *)result);
    return 1;
}

/// Get children in a gameobject
///
/// Parameters :
/// - gameobject pointer
/// - gameobjects name
///
/// Return gameobject children pointers if success and nil otherwise
int GameObject_GetChildren(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = (GameObject *)lua_topointer(L, 1);
    if (gm == 0) {
        lua_pushnil(L);
        return 1;
    }
    std::vector<GameObject *> result = gm->getChildren(lua_tostring(L, 2));
    for (int i = 0; i < result.size(); i++)
        lua_pushlightuserdata(L, (void *)result[i]);
    return (int)result.size();
}

/// Get gameobject name
///
/// Parameters :
/// - asset name / gameobject pointer
///
/// Return name if success and nil otherwise
int GameObject_GetName(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    lua_pushstring(L, gm->name.c_str());
    return 1;
}

/// Set gameobject name
///
/// Parameters :
/// - asset name / gameobject pointer
/// - name
///
/// Return true if success and false otherwise
int GameObject_SetName(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    GameObject * gm = 0;
    if (lua_type(L, 1) == LUA_TSTRING) {
        Asset * asset = Asset::Find(lua_tostring(L, 1));
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    gm->name = lua_tostring(L, 2);
    lua_pushboolean(L, 1);
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D pos = gm->transform().position();
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QQuaternion rot = gm->transform().rotation();
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    QVector3D scale = gm->transform().scale();
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    gm->transform().setPosition(QVector3D(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    gm->transform().setRotation(QQuaternion::fromEulerAngles(QVector3D(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4))));
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
        if (asset == 0 || asset->getData<GameObject>() == 0) {
            lua_pushnil(L);
            return 1;
        }
        gm = asset->getData<GameObject>();
    }
    else
        gm = (GameObject *)lua_topointer(L, 1);
    gm->transform().setScale(QVector3D(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
    lua_pushboolean(L, 1);
    return 1;
}

///////////////////////
////// COMPONENT //////
///////////////////////

/// Get gameobject of a component
///
/// Parameters :
/// - component pointer
///
/// Return gameobject if success and nil otherwise
int Component_GetGameObject(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    Component * comp = (Component *)lua_topointer(L, 1);
    lua_pushlightuserdata(L, (void *)&comp->gameObject());
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

////////////////////
////// CAMERA //////
////////////////////

/// Get main camera
int Camera_GetMain(void * state) {
    lua_pushlightuserdata((lua_State *)state, (void *)Camera::mainCamera);
    return 1;
}

/// Get camera ray by screen coordinates
///
/// Parameters :
/// - x coordinate
/// - y coordinate
///
/// Return x, y, z, dir_x, dir_y, dir_z if success and nil otherwise
int Camera_GetRay(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Ray ray = Camera::mainCamera->getRay((int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2));
    lua_pushnumber(L, ray.origin.x());
    lua_pushnumber(L, ray.origin.y());
    lua_pushnumber(L, ray.origin.z());
    lua_pushnumber(L, ray.direction.x());
    lua_pushnumber(L, ray.direction.y());
    lua_pushnumber(L, ray.direction.z());
    return 6;
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

//////////////////////////
////// BOX COLLIDER //////
//////////////////////////

/// Get box collider offset
///
/// Parameters :
/// - box collider pointer
///
/// Return x, y, z if success and nil otherwise
int BoxCollider_GetOffset(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    BoxCollider * bc = (BoxCollider *)lua_topointer(L, 1);
    if (bc == 0)
        lua_pushnil(L);
    lua_pushnumber(L, bc->offset.x());
    lua_pushnumber(L, bc->offset.y());
    lua_pushnumber(L, bc->offset.z());
    return 3;
}

/// Set box collider offset
///
/// Parameters :
/// - box collider pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int BoxCollider_SetOffset(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    BoxCollider * bc = (BoxCollider *)lua_topointer(L, 1);
    if (bc == 0)
        lua_pushboolean(L, 0);
    bc->offset.setX(lua_tonumber(L, 2));
    bc->offset.setY(lua_tonumber(L, 3));
    bc->offset.setZ(lua_tonumber(L, 4));
    lua_pushboolean(L, 1);
    return 1;
}

/// Get box collider size
///
/// Parameters :
/// - box collider pointer
///
/// Return x, y, z if success and nil otherwise
int BoxCollider_GetSize(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushnil(L);
        return 1;
    }
    BoxCollider * bc = (BoxCollider *)lua_topointer(L, 1);
    if (bc == 0)
        lua_pushnil(L);
    lua_pushnumber(L, bc->size.x());
    lua_pushnumber(L, bc->size.y());
    lua_pushnumber(L, bc->size.z());
    return 3;
}

/// Set box collider size
///
/// Parameters :
/// - box collider pointer
/// - x coordinate
/// - y coordinate
/// - z coordinate
///
/// Return true if success and false otherwise
int BoxCollider_SetSize(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 4) {
        lua_pushboolean(L, 0);
        return 1;
    }
    BoxCollider * bc = (BoxCollider *)lua_topointer(L, 1);
    if (bc == 0)
        lua_pushboolean(L, 0);
    bc->size.setX(lua_tonumber(L, 2));
    bc->size.setY(lua_tonumber(L, 3));
    bc->size.setZ(lua_tonumber(L, 4));
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

////////////////////
////// SCRIPT //////
////////////////////

/// Get script variable
///
/// Parameters :
/// - script pointer
/// - variable name
///
/// Return variable if success and nil otherwise
int Script_GetVariable(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    ScriptComponent * scpt = (ScriptComponent *)lua_topointer(L, 1);
    if (scpt == 0) {
        lua_pushnil(L);
        return 1;
    }
    LuaScript lscpt_dest(state);
    lscpt_dest.pushVariable(scpt->script.getVariable(lua_tostring(L, 2)));
    return 1;
}

/// Get script variable
///
/// Parameters :
/// - script pointer
/// - function name
///
/// Return function return if success and nil otherwise
int Script_CallFunction(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 2) {
        lua_pushnil(L);
        return 1;
    }
    ScriptComponent * scpt = (ScriptComponent *)lua_topointer(L, 1);
    if (scpt == 0) {
        lua_pushnil(L);
        return 1;
    }
    LuaScript lscpt_dest(state);
    std::vector<LuaScript::Variable> args;
    for (int i = 0, sz = argc - 2; i < sz; i++)
        args.push_back(lscpt_dest.getVariable(i + 3));
    std::vector<LuaScript::Variable> results = scpt->script.callFunction(lua_tostring(L, 2), args.data(), argc - 2);
    for (int i = 0; i < results.size(); i++)
        lscpt_dest.pushVariable(results[i]);
    return (int)results.size();
}

////////////////////
////// UIPANEL //////
////////////////////

/// Set UIPanel position
///
/// Parameters :
/// - ui panel pointer
/// - x coordinate
/// - y coordinate
///
/// Return true if success and false otherwise
int UIPanel_SetPosition(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 3) {
        lua_pushboolean(L, 0);
        return 1;
    }
    UIPanel * panel = (UIPanel *)lua_topointer(L, 1);
    panel->position.setX(lua_tonumber(L, 2));
    panel->position.setY(lua_tonumber(L, 3));
    lua_pushboolean(L, 1);
    return 1;
}

////////////////////
////// SCRIPT //////
////////////////////

/// Send raycast and return first touched object
///
/// Parameters :
/// - x coordinate
/// - y coordinate
/// - z coordinate
/// - dir_x coordinate
/// - dir_y coordinate
/// - dir_z coordinate
///
/// Return (collider, x, y, z) * NB_COLLIDED if success and nil otherwise
int Physics_Raycast(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 6) {
        lua_pushnil(L);
        return 1;
    }
    Ray ray(QVector3D(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3)),
            QVector3D(lua_tonumber(L, 4), lua_tonumber(L, 5), lua_tonumber(L, 6)));
    ray.direction.normalize();
    std::vector<std::pair<Collider *, float>> res = Collider::Raycast(ray);
    for (unsigned int i = 0; i < res.size(); i++) {
        lua_pushlightuserdata(L, (void *)&res[i].first->gameObject());
        QVector3D point = ray.origin + ray.direction * res[i].second;
        lua_pushnumber(L, point.x());
        lua_pushnumber(L, point.y());
        lua_pushnumber(L, point.z());
    }
    return (int)(res.size() * 4);
}

///////////////////
////// SOUND //////
///////////////////

/// Play sound
///
///  Parameters :
/// - sound asset name
/// - volume (optional)
///
/// Return true if success and false otherwise
int Sound_Play(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Asset * asset = Asset::Find(lua_tostring(L, 1));
    if (asset == 0 || asset->getData<QUrl>() == 0) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Scene::player.setMedia(*asset->getData<QUrl>());
    if (argc > 1)
        Scene::player.setVolume(lua_tointeger(L, 2));
    Scene::player.play();
    lua_pushboolean(L, 1);
    return 1;
}

/// Stop sound
int Sound_Stop(void * state) {
    Scene::player.stop();
    return 0;
}

/// Get volume
int Sound_GetVolume(void * state) {
    lua_tonumber((lua_State *)state, Scene::player.volume());
    return 1;
}

/// Set volume
///
///  Parameter :
/// - volume
///
/// Return true if success and false otherwise
int Sound_SetVolume(void * state) {
    lua_State * L = (lua_State *)state;
    int argc = lua_gettop(L);
    if (argc < 1) {
        lua_pushboolean(L, 0);
        return 1;
    }
    Scene::player.setVolume(lua_tointeger(L, 1));
    lua_pushboolean(L, 1);
    return 1;
}

}

void LuaScript::loadLibScript() {
    lua_State * L = (lua_State *)state;

    lua_pushcfunction(L, (lua_CFunction)LuaLib::Print);
    lua_setglobal(L, "print");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Split);
    lua_setglobal(L, "split");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GetPrefab);
    lua_setglobal(L, "GetPrefab");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GetTime);
    lua_setglobal(L, "GetTime");

    /// GAMEOBJECT ///

    lua_createtable(L, 0, 0);
    int id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_AddComponent);
    lua_setfield(L, id, "AddComponent");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetComponent);
    lua_setfield(L, id, "GetComponent");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_Instanciate);
    lua_setfield(L, id, "Instanciate");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_Copy);
    lua_setfield(L, id, "Copy");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_Find);
    lua_setfield(L, id, "Find");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_AddChild);
    lua_setfield(L, id, "AddChild");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetChild);
    lua_setfield(L, id, "GetChild");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetChildren);
    lua_setfield(L, id, "GetChildren");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_GetName);
    lua_setfield(L, id, "GetName");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::GameObject_SetName);
    lua_setfield(L, id, "SetName");
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
    lua_setglobal(L, "GameObject");

    /// COMPONENT ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Component_GetGameObject);
    lua_setfield(L, id, "GetGameObject");
    lua_setglobal(L, "Component");

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

    /// CAMERA ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Camera_GetMain);
    lua_setfield(L, id, "GetMain");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Camera_GetRay);
    lua_setfield(L, id, "GetRay");
    lua_setglobal(L, "Camera");

    /// RIGIDBODY ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Rigidbody_GetGravity);
    lua_setfield(L, id, "GetGravity");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Rigidbody_SetGravity);
    lua_setfield(L, id, "SetGravity");
    lua_setglobal(L, "Rigidbody");

    /// BOX COLLIDER ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::BoxCollider_GetOffset);
    lua_setfield(L, id, "GetOffset");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::BoxCollider_SetOffset);
    lua_setfield(L, id, "SetOffset");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::BoxCollider_GetSize);
    lua_setfield(L, id, "GetSize");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::BoxCollider_SetSize);
    lua_setfield(L, id, "SetSize");
    lua_setglobal(L, "BoxCollider");

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

    /// SCRIPT ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Script_GetVariable);
    lua_setfield(L, id, "GetVariable");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Script_CallFunction);
    lua_setfield(L, id, "CallFunction");
    lua_setglobal(L, "Script");

    /// PHYSICS ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Physics_Raycast);
    lua_setfield(L, id, "Raycast");
    lua_setglobal(L, "Physics");

    /// UIPANEL ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::UIPanel_SetPosition);
    lua_setfield(L, id, "SetPosition");
    lua_setglobal(L, "UIPanel");

    /// SOUND ///

    lua_createtable(L, 0, 0);
    id = lua_gettop(L);
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Sound_Play);
    lua_setfield(L, id, "Play");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Sound_Stop);
    lua_setfield(L, id, "Stop");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Sound_GetVolume);
    lua_setfield(L, id, "GetVolume");
    lua_pushcfunction(L, (lua_CFunction)LuaLib::Sound_SetVolume);
    lua_setfield(L, id, "SetVolume");
    lua_setglobal(L, "Sound");
}
