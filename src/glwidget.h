#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "gameobject/gameobject.h"

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

    // Texture par défaut
    static const char * DefaultTexture;

private:

    // Timer d'update
    QBasicTimer updateTimer;

    // Timer inter-update
    QElapsedTimer elapsedTimer;

    // Shader
    QOpenGLShaderProgram program;

    // Matrice de projection
    QMatrix4x4 projection;

    // Texture
    QOpenGLTexture * texture;

    GameObject gameObject;

public:

    // Constructeur par défaut
    explicit GLWidget(QWidget *parent = 0);

    // Destructeur
    ~GLWidget();

private:

    // Initialise les shaders
    void initShaders();

    // Initialise la texture par défaut
    void initTexture();

protected:

    // Appelé lors d'un update
    void timerEvent(QTimerEvent *e) override;

    // Initialise les éléments liés à OpenGL
    void initializeGL() override;

    // Appelé lorsque le widget est redimensionné
    void resizeGL(int w, int h) override;

    // Appelé lors du rendu
    void paintGL() override;

};

#endif // GLWIDGET_H
