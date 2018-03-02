#ifndef FMESH_H
#define FMESH_H

#include "fopenglfunctions.h"
#include "fglobal.h"
#include <QVector>

class FMesh : public FOpenGLFunctions
{
public:

    FMesh(QOpenGLWidget * widget);

    bool load(const QString & path);

    void draw(GLuint programShader);

private:

    void setupMesh();

private:

    bool              m_isValid;

    QVector<FVertex>  m_vertexs;
    QVector<GLuint>   m_indices;
    QVector<FTexture> m_textures;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

#endif // FMESH_H
