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
    m_timer = new MMTimer(20, this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    // shader
    m_shader = new FShader(":/res/vertexShader.txt", ":/res/fragmentShader.txt");
    if( !m_shader->init(this) )
    {
        qWarning()<<"FShader init error.";
        return;
    }

    // openGL
    glEnable(GL_DEPTH_TEST);

    // ------------------------------------
    coordTransform();

    m_timer->start();
}

void MyOpenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // do something
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::coordTransform()
{
    m_shader->use();

    float screenWidth  = 800;
    float screenHeight = 600;

    // model
    GLint modelLocation = glGetUniformLocation(m_shader->id(), "model");
    if( modelLocation != -1 )
    {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    }

    // view
    GLint viewLocation = glGetUniformLocation(m_shader->id(), "view");
    if( viewLocation != -1 )
    {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    }

    // projection
    GLint projectionLocation = glGetUniformLocation(m_shader->id(), "projection");
    if( projectionLocation != -1 )
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }

    repaint();
}

void MyOpenGL::onTimeout()
{
}
