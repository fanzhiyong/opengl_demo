#include "fmesh.h"
#include <QDebug>
#include "fshader.h"

FMesh::FMesh(QOpenGLWidget * widget)
{
    attachOpenGLFunctions(widget);

    m_isValid = false;

    // do something
}

void FMesh::parse(aiMesh *mesh)
{
    //
}

void FMesh::draw(FShader *shader)
{
    if( !m_isValid ) return;

    // texture
    int textureStartPos = 0;
    bindTexture(shader, textureStartPos, FDiffuseTexture);
    bindTexture(shader, textureStartPos, FSpecularTexture);

    // mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}

void FMesh::setupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // copy data
    glBufferData(GL_ARRAY_BUFFER, m_vertexs.size() * sizeof(FVertex), m_vertexs.data(), GL_STATIC_DRAW);

    // ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, texCoords));

    glBindVertexArray(0);
}

void FMesh::bindTexture(FShader * shader, int &pos, FTextureType type)
{
    int number = 0;
    for( int i = 0; i < m_textures.size(); i++ )
    {
        if( m_textures[i].type == type )
        {
            // do something
            glActiveTexture(GL_TEXTURE0 + pos++);
            QString name = type == FDiffuseTexture ? "texture_diffuse" : "texture_specular";
            shader->setValue("material." + name + QString::number(number++), i);
            glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
        }
    }
}
