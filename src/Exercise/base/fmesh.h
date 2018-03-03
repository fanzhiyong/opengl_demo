#ifndef FMESH_H
#define FMESH_H

#include "fopenglfunctions.h"
#include "fglobal.h"
#include <QVector>

class FShader;
class aiMesh;

class FMesh : public FOpenGLFunctions
{
public:

    FMesh(QOpenGLWidget * widget);

    void parse(aiMesh * mesh);

    void draw(FShader * shader);

private:

    void setupMesh();

    void bindTexture(FShader * shader, int & pos, FTextureType type);

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
