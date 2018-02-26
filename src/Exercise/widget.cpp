#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_openGL = new MyOpenGL(this);
    ui->verticalLayout->addWidget(m_openGL);
}

Widget::~Widget()
{
    delete ui;
}
