#include "myopengl.h"
#include <QDebug>
#include <QFile>

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    GLuint vertexShader, fragmentShader;
    // vertex shader
    if( !createShader(vertexShader, GL_VERTEX_SHADER, getShaderSource(":/res/vertexShader.txt")) )
    {
        return;
    }
    // fragment shader
    if( !createShader(fragmentShader, GL_FRAGMENT_SHADER, getShaderSource(":/res/fragmentShader.txt")) )
    {
        return;
    }

    // program
    // link shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // clear
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // use
    glUseProgram(shaderProgram);

    // init
    init();
}

void MyOpenGL::paintGL()
{
    glClearColor(0.0f, 0.168f, 0.211f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::init()
{
    // do something
}

QString MyOpenGL::getShaderSource(const QString &fileName)
{
    QFile file(fileName);
    if( file.open(QIODevice::ReadOnly) )
    {
        return file.readAll();
    }

    return "";
}

bool MyOpenGL::checkShaderCompileStatus(GLuint id)
{
    int  success;
    char infoLog[512] = {0};
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        qInfo()<<infoLog;
        return false;
    }
    else
    {
        return true;
    }
}

bool MyOpenGL::createShader(GLuint & id, int shaderType, const QString & shaderSource)
{
    std::string strShaderSource = shaderSource.toStdString();
    const char * source = strShaderSource.c_str();
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    return checkShaderCompileStatus(id);
}
