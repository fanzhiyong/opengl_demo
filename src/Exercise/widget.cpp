#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QFile>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_openGL = new MyOpenGL(this);
    ui->verticalLayout->addWidget(m_openGL);

    // QSS
    setQss();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setQss()
{
    QFile file(":/res/style.qss");
    if( file.open(QIODevice::ReadOnly) )
    {
        setStyleSheet(file.readAll());
        file.close();
    }
}
