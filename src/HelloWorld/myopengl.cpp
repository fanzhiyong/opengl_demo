#include "myopengl.h"
#include <QDebug>

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    GLuint vertexShader, fragmentShader;
    QString vertexShaderSource =
            "#version 330 core\n"
            "layout(location = 0) in vec3 aPos;\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "   color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "}\n";

    QString fragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec4 color;\n"
            "void main()\n"
            "{\n"
            "	FragColor = color;\n"
            "}\n";

    // vertex shader
    if( !createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource) )
    {
        return;
    }
    // fragment shader
    if( !createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource) )
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::init()
{
    // 数据
    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
        // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
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
