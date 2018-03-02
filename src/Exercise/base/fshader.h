#ifndef FSHADER_H
#define FSHADER_H

#include <QString>
#include "fopenglfunctions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FShader : public FOpenGLFunctions
{
public:
    FShader(QOpenGLWidget * widget, const QString & vertexShaderPath = "", const QString & fragmentShaderPath = "");

    void use();

    void resize(int w, int h);

    GLuint id();

    void setValue(const QString & name, glm::mat4 value);

private:

    void init(QOpenGLWidget * widget);

    bool createShader(GLuint & id, int shaderType, const QString & shaderSource);

    bool checkShaderCompileStatus(GLuint id);

    QString getShaderSource(const QString &fileName);

    void transform();

private:

    QString m_vertexShaderPath;
    QString m_fragmentShaderPath;

    GLuint  m_shaderProgram;
};

#endif // FSHADER_H
