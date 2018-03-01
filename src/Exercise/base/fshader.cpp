#include "fshader.h"
#include <QDebug>
#include <QFile>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

FShader::FShader(QOpenGLWidget *widget, const QString &vertexShaderPath, const QString &fragmentShaderPath)
{
    m_vertexShaderPath   = vertexShaderPath;
    m_fragmentShaderPath = fragmentShaderPath;

    m_shaderProgram = 0;

    // init
    init(widget);
}

void FShader::init(QOpenGLWidget *widget)
{
    attachOpenGLFunctions(widget);

    GLuint vertexShader, fragmentShader;
    // vertex shader
    if( !createShader(vertexShader, GL_VERTEX_SHADER, getShaderSource(m_vertexShaderPath)) )
    {
        return;
    }

    // fragment shader
    if( !createShader(fragmentShader, GL_FRAGMENT_SHADER, getShaderSource(m_fragmentShaderPath)) )
    {
        return;
    }

    // link shader
    m_shaderProgram = core()->glCreateProgram();
    core()->glAttachShader(m_shaderProgram, vertexShader);
    core()->glAttachShader(m_shaderProgram, fragmentShader);
    core()->glLinkProgram(m_shaderProgram);
    // clear
    core()->glDeleteShader(vertexShader);
    core()->glDeleteShader(fragmentShader);

    // default model
    transform();
}

void FShader::use()
{
    core()->glUseProgram(m_shaderProgram);
}

void FShader::resize(int w, int h)
{
    use();

    // projection
    GLint projectionLocation = core()->glGetUniformLocation(m_shaderProgram, "projection");
    if( projectionLocation != -1 )
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), w / (float)h, 0.1f, 100.0f);
        core()->glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }
}

GLuint FShader::id()
{
    return m_shaderProgram;
}

bool FShader::createShader(GLuint & id, int shaderType, const QString & shaderSource)
{
    std::string strShaderSource = shaderSource.toStdString();
    const char * source = strShaderSource.c_str();
    id = core()->glCreateShader(shaderType);
    core()->glShaderSource(id, 1, &source, NULL);
    core()->glCompileShader(id);

    return checkShaderCompileStatus(id);
}

bool FShader::checkShaderCompileStatus(GLuint id)
{
    int  success;
    char infoLog[512] = {0};
    core()->glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        core()->glGetShaderInfoLog(id, 512, NULL, infoLog);
        qWarning()<<infoLog;
        return false;
    }
    else
    {
        return true;
    }
}

QString FShader::getShaderSource(const QString &fileName)
{
    QFile file(fileName);
    if( file.open(QIODevice::ReadOnly) )
    {
        return file.readAll();
    }

    return "";
}

void FShader::transform()
{
    use();

    // model
    GLint modelLocation = core()->glGetUniformLocation(m_shaderProgram, "model");
    if( modelLocation != -1 )
    {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f));
        core()->glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    }

    // view
    GLint viewLocation = core()->glGetUniformLocation(m_shaderProgram, "view");
    if( viewLocation != -1 )
    {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
        core()->glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    }
}
