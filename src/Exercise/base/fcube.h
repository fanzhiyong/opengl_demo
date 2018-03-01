#ifndef FCUBE_H
#define FCUBE_H

#include "fopenglfunctions.h"

class FCube : public FOpenGLFunctions
{
public:
    FCube(QOpenGLWidget * widget);

    void draw(GLuint programShader, float x = 0.0f, float y = 0.0f, float z = 0.0f,
              float angle = 0.0f);

private:

    void init();

    void transform(GLuint programShader, float x, float y, float z, float angle);

private:

    GLuint m_vao;
    GLuint m_vbo;
};

#endif // FCUBE_H
