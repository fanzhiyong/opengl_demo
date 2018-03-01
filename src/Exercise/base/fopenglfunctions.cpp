#include "fopenglfunctions.h"
#include <QOpenGLWidget>
#include <QOpenGLContext>

FOpenGLFunctions::FOpenGLFunctions(QOpenGLFunctions_3_3_Core * core)
{
    m_core = core;
}

void FOpenGLFunctions::attachOpenGLFunctions(QOpenGLWidget *widget)
{
    m_core = widget->context()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

QOpenGLFunctions_3_3_Core *FOpenGLFunctions::core()
{
    return m_core;
}
