#ifndef FMODEL_H
#define FMODEL_H

#include "fopenglfunctions.h"
#include "fmesh.h"

class aiScene;
class aiNode;

class FModel : public FOpenGLFunctions
{
public:
    FModel(QOpenGLWidget * widget);

    bool load(const QString & path);

    void draw(FShader * shader);

private:

    void parseMesh(const aiScene *scene, aiNode *node);

    void clear();

private:

    QList<FMesh *> m_meshs;
};

#endif // FMODEL_H
