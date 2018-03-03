#ifndef FGLOBAL_H
#define FGLOBAL_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct FVertex
{
    FVertex()
    {
        position  = glm::vec3(0.0f, 0.0f, 0.0f);
        normal    = glm::vec3(0.0f, 0.0f, 0.0f);
        texCoords = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    glm::vec3 position;     // 位置
    glm::vec3 normal;       // 法线
    glm::vec3 texCoords;    // 纹理坐标
};

enum FTextureType
{
    FDiffuseTexture,    // 漫反射
    FSpecularTexture    // 镜面反射
};

struct FTexture
{
    FTexture()
    {
        id   = 0;
        type = FDiffuseTexture;
    }

    unsigned int id;
    FTextureType type;
};


#endif // FGLOBAL_H
