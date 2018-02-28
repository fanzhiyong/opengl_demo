#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "mmtimer.h"

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

    void transform();

    void coordTransform();

    void mousePressEvent(QMouseEvent * event);

    void mouseReleaseEvent(QMouseEvent * event);

    void mouseMoveEvent(QMouseEvent * event);

private slots:

    void onTimeout();

private:

    bool        m_pressed;
    QPoint      m_pressPoint;
    float       m_x;

    GLuint      m_shaderProgram;
    GLuint      m_vao;
    GLuint      m_vbo;

    GLuint      m_texture;

    MMTimer   * m_timer;

    float       m_rValue;
};

#endif // MYOPENGL_H
