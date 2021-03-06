﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myopengl.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

private:

    Ui::Widget *ui;

    MyOpenGL * m_openGL;
};

#endif // WIDGET_H
