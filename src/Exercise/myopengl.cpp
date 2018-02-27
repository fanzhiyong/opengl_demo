#include "myopengl.h"
#include <QDebug>
#include <QFile>
#include <QImage>

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{
    m_rValue = 0.0f;

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
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
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    // clear
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // use
    glUseProgram(m_shaderProgram);

    // init
    init();
}

void MyOpenGL::paintGL()
{
    glClearColor(0.0f, 0.168f, 0.211f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // texture
    glBindTexture(GL_TEXTURE_2D, m_texture);
    // draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_QUADS, 0, 4);
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::init()
{
    float vertices[] = {
        // pos color texture-coord
        -0.8f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.8f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.8f,  -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.8f, -0.8f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f
    };

    // VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture
    QImage image(":/res/timg.jpg");
    // convert to RGBA
    QImage imageRGBA = image.convertToFormat(QImage::Format_RGBA8888);


    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageRGBA.bits());
    // 参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    m_timer->start();
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

void MyOpenGL::onTimeout()
{
//    m_rValue += 0.05f;
//    if( m_rValue > 1.0f )
//    {
//        m_rValue = 0.0f;
//    }

//    // set uniform
//    GLint location = glGetUniformLocation(m_shaderProgram, "testColor");
//    if( location != -1 )
//    {
//        glUseProgram(m_shaderProgram);
//        glUniform4f(location, m_rValue, 0.0f, 0.0f, 1.0f);
//        update();
//    }
}
