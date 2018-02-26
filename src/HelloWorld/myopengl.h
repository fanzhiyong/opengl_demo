#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>

class MyOpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGL(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

private:

    void init();

    bool checkShaderCompileStatus(GLuint id);

    bool createShader(GLuint & id, int shaderType, const QString & shaderSource);

private:

    GLuint m_vbo;
    GLuint m_vao;
};

#endif // MYOPENGL_H
