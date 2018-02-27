#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QTimer>

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

    QString getShaderSource(const QString & fileName);

    bool checkShaderCompileStatus(GLuint id);

    bool createShader(GLuint & id, int shaderType, const QString & shaderSource);

private slots:

    void onTimeout();

private:

    GLuint      m_shaderProgram;
    GLuint      m_vao;
    GLuint      m_vbo;

    GLuint      m_texture;

    QTimer    * m_timer;

    float       m_rValue;
};

#endif // MYOPENGL_H
