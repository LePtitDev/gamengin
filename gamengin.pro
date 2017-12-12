#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T21:49:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gamengin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    src/mainwindow.cpp \
    src/glwidget.cpp \
    src/gameobject/gameobject.cpp \
    src/gameobject/component.cpp \
    src/gameobject/transform.cpp \
    src/gameobject/geometry.cpp \
    src/gameobject/particle_system.cpp \
    src/geometry/mesh.cpp \
    src/geometry/shapes.cpp \
    src/gameobject/material.cpp \
    src/gameobject/rigidbody.cpp \
    src/gameobject/camera.cpp \
    src/controller/camera_rts.cpp \
    src/controller/camera_facing.cpp \
    src/script/lua.cpp \
    \
    include/lua/lapi.c \
    include/lua/lcode.c \
    include/lua/lctype.c \
    include/lua/ldebug.c \
    include/lua/ldo.c \
    include/lua/ldump.c \
    include/lua/lfunc.c \
    include/lua/lgc.c \
    include/lua/llex.c \
    include/lua/lmem.c \
    include/lua/lobject.c \
    include/lua/lopcodes.c \
    include/lua/lparser.c \
    include/lua/lstate.c \
    include/lua/lstring.c \
    include/lua/ltable.c \
    include/lua/ltm.c \
    include/lua/lundump.c \
    include/lua/lvm.c \
    include/lua/lzio.c \
    \
    include/lua/lauxlib.c \
    include/lua/lbaselib.c \
    include/lua/lbitlib.c \
    include/lua/lcorolib.c \
    include/lua/ldblib.c \
    include/lua/liolib.c \
    include/lua/lmathlib.c \
    include/lua/loslib.c \
    include/lua/lstrlib.c \
    include/lua/ltablib.c \
    include/lua/lutf8lib.c \
    include/lua/loadlib.c \
    include/lua/linit.c \
    src/assets/assets.cpp


HEADERS += \
    src/mainwindow.h \
    src/glwidget.h \
    src/gameobject/gameobject.h \
    src/gameobject/transform.h \
    src/gameobject/component.h \
    src/gameobject/geometry.h \
    src/gameobject/particle_system.h \
    src/geometry/mesh.h \
    src/geometry/shapes.h \
    src/gameobject/material.h \
    src/gameobject/rigidbody.h \
    src/gameobject/camera.h \
    src/controller/camera_rts.h \
    src/controller/camera_facing.h \
    src/script/lua.h \
    \
    include/lua/lapi.h \
    include/lua/lauxlib.h \
    include/lua/lcode.h \
    include/lua/lctype.h \
    include/lua/ldebug.h \
    include/lua/ldo.h \
    include/lua/lfunc.h \
    include/lua/lgc.h \
    include/lua/llex.h \
    include/lua/llimits.h \
    include/lua/lmem.h \
    include/lua/lobject.h \
    include/lua/lopcodes.h \
    include/lua/lparser.h \
    include/lua/lprefix.h \
    include/lua/lstate.h \
    include/lua/lstring.h \
    include/lua/ltable.h \
    include/lua/ltm.h \
    include/lua/lua.h \
    include/lua/lua.hpp \
    include/lua/luaconf.h \
    include/lua/lualib.h \
    include/lua/lundump.h \
    include/lua/lvm.h \
    include/lua/lzio.h \
    src/assets/assets.h

FORMS += \
	mainwindow.ui

