#include "fmesh.h"
#include <QDebug>

FMesh::FMesh(QOpenGLWidget * widget)
{
    attachOpenGLFunctions(widget);

    m_isValid = false;

    // do something
}

bool FMesh::load(const QString &path)
{
    setupMesh();

    m_isValid = true;
    return true;
}

void FMesh::draw(GLuint programShader)
{
    if( !m_isValid ) return;
}

void FMesh::setupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}
