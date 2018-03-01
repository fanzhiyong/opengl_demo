#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "mmtimer.h"
#include "openglcube.h"
#include "base/fshader.h"

class MyOpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGL(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

private:

    void coordTransform();

private slots:

    void onTimeout();

private:

    FShader       * m_shader;

    MMTimer       * m_timer;
};

#endif // MYOPENGL_H
