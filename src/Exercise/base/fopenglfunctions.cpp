#include "fopenglfunctions.h"
#include <QOpenGLWidget>
#include <QOpenGLContext>

FOpenGLFunctions::FOpenGLFunctions(QOpenGLFunctions_3_3_Core * core)
{
    m_core = core;
    m_openGLWidget = NULL;
}

void FOpenGLFunctions::attachOpenGLFunctions(QOpenGLWidget *widget)
{
    m_core = widget->context()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    m_openGLWidget = widget;
}

QOpenGLFunctions_3_3_Core *FOpenGLFunctions::core()
{
    return m_core;
}

void FOpenGLFunctions::glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    core()->glGenVertexArrays(n, arrays);
}

void FOpenGLFunctions::glBindVertexArray(GLuint array)
{
    core()->glBindVertexArray(array);
}

void FOpenGLFunctions::glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    core()->glDrawArrays(mode, first, count);
}

GLuint FOpenGLFunctions::glCreateProgram()
{
    return core()->glCreateProgram();
}

void FOpenGLFunctions::glAttachShader(GLuint program, GLuint shader)
{
    core()->glAttachShader(program, shader);
}

void FOpenGLFunctions::glLinkProgram(GLuint program)
{
    core()->glLinkProgram(program);
}

void FOpenGLFunctions::glDeleteShader(GLuint shader)
{
    core()->glDeleteShader(shader);
}

void FOpenGLFunctions::glDeleteProgram(GLuint program)
{
    core()->glDeleteProgram(program);
}

void FOpenGLFunctions::glUseProgram(GLuint program)
{
    core()->glUseProgram(program);
}

void FOpenGLFunctions::glGenBuffers(GLsizei n, GLuint *buffers)
{
    core()->glGenBuffers(n, buffers);
}

void FOpenGLFunctions::glBindBuffer(GLenum target, GLuint buffer)
{
    core()->glBindBuffer(target, buffer);
}

void FOpenGLFunctions::glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    core()->glBufferData(target, size, data, usage);
}

void FOpenGLFunctions::glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
    core()->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void FOpenGLFunctions::glEnableVertexAttribArray(GLuint index)
{
    core()->glEnableVertexAttribArray(index);
}

GLint FOpenGLFunctions::glGetUniformLocation(GLuint program, const GLchar *name)
{
    return core()->glGetUniformLocation(program, name);
}

void FOpenGLFunctions::glBindTexture(GLenum target, GLuint texture)
{
    core()->glBindTexture(target, texture);
}

void FOpenGLFunctions::glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    core()->glUniformMatrix4fv(location, count, transpose, value);
}

void FOpenGLFunctions::glUniform1i(GLint location, GLint v0)
{
    core()->glUniform1i(location, v0);
}

void FOpenGLFunctions::glUniform1f(GLint location, GLfloat v0)
{
    core()->glUniform1f(location, v0);
}

GLuint FOpenGLFunctions::glCreateShader(GLenum type)
{
    return core()->glCreateShader(type);
}

void FOpenGLFunctions::glShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length)
{
    core()->glShaderSource(shader, count, string, length);
}

void FOpenGLFunctions::glCompileShader(GLuint shader)
{
    core()->glCompileShader(shader);
}

void FOpenGLFunctions::glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
    core()->glGetShaderiv(shader, pname, params);
}

void FOpenGLFunctions::glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    core()->glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void FOpenGLFunctions::glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    core()->glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void FOpenGLFunctions::glActiveTexture(GLenum texture)
{
    core()->glActiveTexture(texture);
}

void FOpenGLFunctions::glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    core()->glDrawElements(mode, count, type, indices);
}
