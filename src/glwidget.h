#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "gameobject/gameobject.h"

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QBasicTimer>
#include <QElapsedTimer>

#include <QMatrix4x4>
#include <QOpenGLTexture>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {

    Q_OBJECT

public:

    // Taux de rafraichissement par défaut
    static const int DefaultFrameRate;

    // Vertex shader par défaut
    static const char * DefaultVShader;

    // Fragment shader par défaut
    static const char * DefaultFShader;

    // Script d'initialisation du jeu
    static const char * DefaultGameScript;

private:

    // Timer d'update
    QBasicTimer updateTimer;

    // Shader
    QOpenGLShaderProgram program;

public:

    // Constructeur par défaut
    explicit GLWidget(QWidget *parent = 0);

    // Destructeur
    ~GLWidget();

private:

    // Initialise les shaders
    void initShaders();

    // Initialise les scenes et assets du jeu
    void initGame();

protected:

    // Appelé lors d'un update
    void timerEvent(QTimerEvent *e) override;

    // Key press event callback
    void keyPressEvent(QKeyEvent * event) override;

    // Key release event callback
    void keyReleaseEvent(QKeyEvent * event) override;

    // Mouse press event callback
    void mousePressEvent(QMouseEvent * event) override;

    // Mouse release event callback
    void mouseReleaseEvent(QMouseEvent * event) override;

    // Mouse move event callback
    void mouseMoveEvent(QMouseEvent * event) override;

    // Mouse wheel event callback
    void wheelEvent(QWheelEvent * event) override;

    // Initialise les éléments liés à OpenGL
    void initializeGL() override;

    // Appelé lorsque le widget est redimensionné
    void resizeGL(int w, int h) override;

    // Appelé lors du rendu
    void paintGL() override;

};

#endif // GLWIDGET_H
