#include "myopengl.h"
#include <QDebug>
#include <QFile>
#include <QImage>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QMouseEvent>

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{
    m_shader = NULL;
    m_cube   = NULL;

    m_timer = new MMTimer(20, this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    // shader
    m_shader = new FShader(this, ":/res/vertexShader.txt", ":/res/fragmentShader.txt");
    // cube
    m_cube   = new FCube(this);

    // openGL
    glEnable(GL_DEPTH_TEST);

    m_timer->start();
}

void MyOpenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // do something
    m_cube->draw(m_shader->id(), -1.0f, -1.0f, -1.0f);
}

void MyOpenGL::resizeGL(int w, int h)
{
    if( h == 0 ) h = 1;

    glViewport(0, 0, w, h);
    m_shader->resize(w, h);
}

void MyOpenGL::onTimeout()
{
}
