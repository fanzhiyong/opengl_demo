#include "fmodel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QDebug>

FModel::FModel(QOpenGLWidget * widget)
{
    attachOpenGLFunctions(widget);
}

bool FModel::load(const QString &path)
{
    clear();

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.toStdString().c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if( scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == NULL )
    {
        qWarning()<<"load "<<path<<" error. reason: "<<importer.GetErrorString();
        return false;
    }

    // parser mesh
    parseMesh(scene, scene->mRootNode);

    return true;
}

void FModel::draw(FShader *shader)
{
    for( int i = 0; i < m_meshs.size(); i++ )
    {
        m_meshs[i]->draw(shader);
    }
}

void FModel::parseMesh(const aiScene *scene, aiNode *node)
{
    if( scene == NULL || node == NULL ) return;

    // current
    for( unsigned int i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
        FMesh * tmp = new FMesh(m_openGLWidget);
        //tmp->parse(mesh);
        m_meshs.push_back(tmp);
    }

    // sub
    for( unsigned int i = 0; i < node->mNumChildren; i++ )
    {
        parseMesh(scene, node->mChildren[i]);
    }
}

void FModel::clear()
{
    for( int i = 0 ; i < m_meshs.size(); i++ )
    {
        delete m_meshs[i];
    }

    m_meshs.clear();
}
