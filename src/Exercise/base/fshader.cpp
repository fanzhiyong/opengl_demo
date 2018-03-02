#include "fshader.h"
#include <QDebug>
#include <QFile>

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
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    // clear
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // default model
    transform();
}

void FShader::use()
{
    glUseProgram(m_shaderProgram);
}

void FShader::resize(int w, int h)
{
    use();

    // projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), w / (float)h, 0.1f, 100.0f);
    setValue("projection", projection);
}

GLuint FShader::id()
{
    return m_shaderProgram;
}

void FShader::setValue(const QString &name, glm::mat4 value)
{
    use();

    GLint location = glGetUniformLocation(m_shaderProgram, name.toStdString().c_str());
    if( location != -1 )
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
        qWarning()<<"no has "<<name<<" value";
    }
}

bool FShader::createShader(GLuint & id, int shaderType, const QString & shaderSource)
{
    std::string strShaderSource = shaderSource.toStdString();
    const char * source = strShaderSource.c_str();
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    return checkShaderCompileStatus(id);
}

bool FShader::checkShaderCompileStatus(GLuint id)
{
    int  success;
    char infoLog[512] = {0};
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
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
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f));
    setValue("model", model);

    // view
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
    setValue("view", view);
}
