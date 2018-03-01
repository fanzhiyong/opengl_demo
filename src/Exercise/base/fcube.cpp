#include "fcube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

FCube::FCube(QOpenGLWidget * widget)
{
    attachOpenGLFunctions(widget);

    m_vao = 0;
    m_vbo = 0;

    init();
}

void FCube::draw(GLuint programShader, float x, float y, float z, float angle)
{
    transform(programShader, x, y, z, angle);

    // do something
    core()->glBindVertexArray(m_vao);
    core()->glDrawArrays(GL_TRIANGLES, 0, 36);
}

void FCube::init()
{
    float vertices[] =
    {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    core()->glGenVertexArrays(1, &m_vao);
    core()->glBindVertexArray(m_vao);

    core()->glGenBuffers(1, &m_vbo);
    core()->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    core()->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    core()->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    core()->glEnableVertexAttribArray(0);
}

void FCube::transform(GLuint programShader, float x, float y, float z, float angle)
{
    core()->glUseProgram(programShader);

    // model
    GLint modelLocation = core()->glGetUniformLocation(programShader, "model");
    if( modelLocation != -1 )
    {
        glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
        matrix = glm::rotate(matrix, glm::radians(angle), glm::vec3(1.0f,0.0f,0.0f));

        core()->glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
