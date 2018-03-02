#ifndef FOPENGLFUNCTIONS_H
#define FOPENGLFUNCTIONS_H

#include <QOpenGLFunctions_3_3_Core>

class QOpenGLWidget;

class FOpenGLFunctions
{
public:
    FOpenGLFunctions(QOpenGLFunctions_3_3_Core * core = NULL);

    void attachOpenGLFunctions(QOpenGLWidget * widget);
    void glGenVertexArrays(GLsizei n, GLuint *arrays);
    void glBindVertexArray(GLuint array);
    void glDrawArrays(GLenum mode, GLint first, GLsizei count);
    GLuint glCreateProgram();
    void glAttachShader(GLuint program, GLuint shader);
    void glLinkProgram(GLuint program);
    void glDeleteShader(GLuint shader);
    void glDeleteProgram(GLuint program);
    void glUseProgram(GLuint program);
    void glGenBuffers(GLsizei n, GLuint *buffers);
    void glBindBuffer(GLenum target, GLuint buffer);
    void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
    void glEnableVertexAttribArray(GLuint index);
    GLint glGetUniformLocation(GLuint program, const GLchar *name);
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length);
    void glCompileShader(GLuint shader);
    void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

private:

    QOpenGLFunctions_3_3_Core * core();

private:

    QOpenGLFunctions_3_3_Core * m_core;
};

#endif // FOPENGLFUNCTIONS_H
