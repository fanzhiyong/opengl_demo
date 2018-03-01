#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "mmtimer.h"
#include "base/fshader.h"
#include "base/fcube.h"

class MyOpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGL(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

private:

private slots:

    void onTimeout();

private:

    FShader       * m_shader;
    FCube         * m_cube;

    MMTimer       * m_timer;
};

#endif // MYOPENGL_H
