#include "fshader.h"
#include <QDebug>
#include <QFile>

FShader::FShader(const QString &vertexShaderPath, const QString &fragmentShaderPath)
{
    m_vertexShaderPath   = vertexShaderPath;
    m_fragmentShaderPath = fragmentShaderPath;

    m_shaderProgram = 0;
}

bool FShader::init(QOpenGLWidget *widget)
{
    attachOpenGLFunctions(widget);

    GLuint vertexShader, fragmentShader;
    // vertex shader
    if( !createShader(vertexShader, GL_VERTEX_SHADER, getShaderSource(m_vertexShaderPath)) )
    {
        return false;
    }

    // fragment shader
    if( !createShader(fragmentShader, GL_FRAGMENT_SHADER, getShaderSource(m_fragmentShaderPath)) )
    {
        return false;
    }

    // link shader
    m_shaderProgram = core()->glCreateProgram();
    core()->glAttachShader(m_shaderProgram, vertexShader);
    core()->glAttachShader(m_shaderProgram, fragmentShader);
    core()->glLinkProgram(m_shaderProgram);
    // clear
    core()->glDeleteShader(vertexShader);
    core()->glDeleteShader(fragmentShader);
}

void FShader::use()
{
    core()->glUseProgram(m_shaderProgram);
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
        qInfo()<<infoLog;
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
