#ifndef FSHADER_H
#define FSHADER_H

#include <QString>
#include "fopenglfunctions.h"

class FShader : public FOpenGLFunctions
{
public:
    FShader(const QString & vertexShaderPath = "", const QString & fragmentShaderPath = "");

    bool init(QOpenGLWidget * widget);

    void use();

    GLuint id();

private:

    bool createShader(GLuint & id, int shaderType, const QString & shaderSource);

    bool checkShaderCompileStatus(GLuint id);

    QString getShaderSource(const QString &fileName);

private:

    QString m_vertexShaderPath;
    QString m_fragmentShaderPath;

    GLuint  m_shaderProgram;
};

#endif // FSHADER_H
