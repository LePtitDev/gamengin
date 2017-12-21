#include "glwidget.h"
#include "gameobject/geometry.h"
#include "gameobject/rigidbody.h"
#include "gameobject/material.h"
#include "gameobject/camera.h"
#include "gameobject/particle_system.h"
#include "controller/camera_rts.h"
#include "controller/camera_facing.h"
#include "geometry/shapes.h"
#include "script/lua.h"
#include "assets/game.h"
#include "assets/scene.h"

#include <iostream>

const int GLWidget::DefaultFrameRate = 60;
const char * GLWidget::DefaultVShader = "./shaders/vshader.glsl";
const char * GLWidget::DefaultFShader = "./shaders/fshader.glsl";
const char * GLWidget::DefaultGameScript = "./assets/game.lua";

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    // On lance le timer d'update
    updateTimer.start(1000 / GLWidget::DefaultFrameRate, this);

    // Active la récupération des événements clavier
    grabKeyboard();
}

GLWidget::~GLWidget() {
    // Définie le contexte courant pour détruire les textures et buffers
    makeCurrent();
    // Detruit les objets OpenGL
    Asset::Clear();
    Scene::ClearScenes();
    Material::defaultTexture().reset();
    doneCurrent();
}



void GLWidget::initShaders() {
    // Compile le vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, GLWidget::DefaultVShader))
        close();

    // Compile le fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, GLWidget::DefaultFShader))
        close();

    // Lie pipeline aux shaders
    if (!program.link())
        close();

    // Attache le pipeline pour être utilisé
    if (!program.bind())
        close();
}

void GLWidget::initGame() {
    LuaScript gameScript;
    Asset::Load("texture:default", "res/default.png");
    Asset * asset = Asset::Load("script:main", DefaultGameScript);
    gameScript.loadLibGame();
    if (asset == 0 || !gameScript.load(asset->getData<std::string>()->c_str())) {
        qInfo() << "Le script principal n'a pas pu être chargé";
        exit(0);
    }
    gameScript.execute();
    if (SceneManager::GetScenes().size() == 0) {
        qInfo() << "Aucune scene n'a été définie";
        exit(0);
    }
}



void GLWidget::timerEvent(QTimerEvent *) {
    Scene::main->update();

    // Met à jour le rendu
    update();
}

void GLWidget::keyPressEvent(QKeyEvent * event) {
    Scene::main->keyPressEvent(event);
}

void GLWidget::keyReleaseEvent(QKeyEvent * event) {
    Scene::main->keyReleaseEvent(event);
}

void GLWidget::mousePressEvent(QMouseEvent * event) {
    Scene::main->mousePressEvent(event);
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event) {
    Scene::main->mouseReleaseEvent(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent * event) {
    Scene::main->mouseMoveEvent(event);
}

void GLWidget::wheelEvent(QWheelEvent * event) {
    Scene::main->wheelEvent(event);
}

void GLWidget::initializeGL() {
    // Initialise les fonctions OpenGL
    initializeOpenGLFunctions();

    // Change la couleur par défaut
    glClearColor(0, 0, 0, 1);

    // Active le buffer de profondeur
    glEnable(GL_DEPTH_TEST);

    // Active le backface culling
    glEnable(GL_CULL_FACE);

    initShaders();
    initGame();
}

void GLWidget::resizeGL(int w, int h) {
    Scene::width = w;
    Scene::height = h;
    Camera::mainCamera->aspect = (float)w / (float)(h ? h : 1);
}

void GLWidget::paintGL() {
    // Réinitialise les buffer de couleur et de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Attache le pipeline pour être utilisé
    if (!program.bind())
        close();

    // Assign projection and view matrix
    Camera::mainCamera->apply(&program);

    // Assigne la texture dans le fragment shader
    program.setUniformValue("texture", 0);

    // Assigne la position de la lumière et  sa couleur
    program.setUniformValue("v_lightpos", QVector3D(0.0f, 5.0f, 0.0f));
    program.setUniformValue("v_lightcolor", QVector3D(1.0f, 1.0f, 1.0f));

    Scene::main->paintGL(&program);
}
