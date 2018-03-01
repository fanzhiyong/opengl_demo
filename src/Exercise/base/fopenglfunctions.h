#ifndef FOPENGLFUNCTIONS_H
#define FOPENGLFUNCTIONS_H

#include <QOpenGLFunctions_3_3_Core>

class QOpenGLWidget;

class FOpenGLFunctions
{
public:
    FOpenGLFunctions(QOpenGLFunctions_3_3_Core * core = NULL);

    void attachOpenGLFunctions(QOpenGLWidget * widget);

    QOpenGLFunctions_3_3_Core * core();

private:

    QOpenGLFunctions_3_3_Core * m_core;
};

#endif // FOPENGLFUNCTIONS_H
