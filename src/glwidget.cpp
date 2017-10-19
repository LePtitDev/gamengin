#include "glwidget.h"
#include "gameobject/geometry.h"
#include "geometry/shapes.h"

#include <iostream>

const int GLWidget::DefaultFrameRate = 60;
const char * GLWidget::DefaultVShader = "./shaders/vshader.glsl";
const char * GLWidget::DefaultFShader = "./shaders/fshader.glsl";
const char * GLWidget::DefaultTexture = "./res/default.png";

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    // On lance le timer d'update
    updateTimer.start(1000 / GLWidget::DefaultFrameRate, this);

    // On lance le timer inter-update
    elapsedTimer.start();
}

GLWidget::~GLWidget() {
    // Définie le contexte courant pour détruire les textures et buffers
    makeCurrent();
    delete texture;
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

void GLWidget::initTexture() {
    // Charge la texture par défaut
    texture = new QOpenGLTexture(QImage(GLWidget::DefaultTexture).mirrored());

    // Assigne le mode de filtrage pour la minification de la texture en "plus proche voisin"
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Assigne le mode de filtrage pour la magnification de la texture en "linéaire"
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Définie la texture comme étant répétitive
    texture->setWrapMode(QOpenGLTexture::Repeat);
}



void GLWidget::timerEvent(QTimerEvent *e) {
    // Relance le timer inter-update
    this->elapsedTimer.restart();

    // Met à jour le rendu
    update();
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
    initTexture();

    gameObject.transform().position.setZ(-5.0f);
    gameObject.addComponent<Geometry>();
    GeometryCube(gameObject.getComponent<Geometry>());
}

void GLWidget::resizeGL(int w, int h) {
    // Calcule le rapport entre la largeur et la hauteur
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Initialise les valeurs du FOV, du near et du far
    const qreal zNear = 1.0, zFar = 30.0, fov = 45.0;

    // Charge la matrice d'identitée
    projection.setToIdentity();

    // Ajoute une projection en perspective
    projection.perspective(fov, aspect, zNear, zFar);
}

void GLWidget::paintGL() {
    // Réinitialise les buffer de couleur et de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attache le pipeline pour être utilisé
    if (!program.bind())
        close();

    // Attache la texture pour être utilisée
    texture->bind();

    // Matrice de transformation
    QMatrix4x4 matrix(projection);

    // Assigne la texture dans le fragment shader
    program.setUniformValue("texture", 0);

    gameObject.paintGL(&program, matrix);
}
