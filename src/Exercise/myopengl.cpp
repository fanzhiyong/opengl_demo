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
    m_rValue = 0.0f;

    m_x = 0.0f;

    m_pressed = false;

    m_timer = new MMTimer(10, this);
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    // init
    init();
}

void MyOpenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // draw
    glBindVertexArray(m_vao);

    QList<glm::vec3> cubePositions =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glUseProgram(m_shaderProgram);
    for( int i = 0; i < cubePositions.size(); i++ )
    {
        // model
        GLint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
        if( modelLocation != -1 )
        {
            glm::mat4 rotationMatrix = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            //glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

//    glUseProgram(m_shaderProgram);
//    GLint rotateLocation = glGetUniformLocation(m_shaderProgram, "transform");
//    if( rotateLocation != -1 )
//    {
//        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f,0.0f,1.0f));
//        glUniformMatrix4fv(rotateLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
//    }
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::init()
{
    float vertices[] =
    {
        // 上
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        // 下
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        // 左
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        // 右
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        // 前
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        // 后
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

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
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

    //transform();
    coordTransform();

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

void MyOpenGL::transform()
{
    static GLfloat angle = 0.0f;

    angle += 1.0f;
    if( angle > 360.0f )
    {
        angle = 0.0f;
    }

    glUseProgram(m_shaderProgram);
    GLint rotateLocation = glGetUniformLocation(m_shaderProgram, "transform");
    if( rotateLocation != -1 )
    {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(rotateLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

        update();
    }
}

void MyOpenGL::coordTransform()
{
    glUseProgram(m_shaderProgram);

    float screenWidth  = 800;
    float screenHeight = 600;

    // model
    GLint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
    if( modelLocation != -1 )
    {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    }

    // view
    GLint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
    if( viewLocation != -1 )
    {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    }

    // projection
    GLint projectionLocation = glGetUniformLocation(m_shaderProgram, "projection");
    if( projectionLocation != -1 )
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }

    update();
}

void MyOpenGL::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_pressPoint = event->pos();
    m_pressed    = true;
}

void MyOpenGL::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QPoint diff = m_pressPoint - event->pos();
    m_x = (diff.x() / 60.0f) * 360 + m_x;

    m_pressed = false;
}

void MyOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    if( m_pressed )
    {
//        QPoint diff = event->pos() - m_pressPoint;

//        float x = (diff.x() / 400.0f) * 360 + m_x;
//        float y = (diff.y() / 40.0f) * 360;
//        qInfo()<<x;

//        // 改变模型
//        glUseProgram(m_shaderProgram);

//        GLint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
//        if( modelLocation != -1 )
//        {
//            // x
//            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(0.0f,1.0f,0.0f));
//            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(y), glm::vec3(1.0f,0.0f,0.0f));
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
//        }

//        update();
    }
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

    //transform();
}
