#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setStyleSheet("QLabel{color:red;"
                             "background-color:rgb(0,255,255);}");

    //给标签添加样式
    ui->label->setStyleSheet("QLabel{color:blue;"
                             "background-color:rgb(0,255,255);"
                             "border-image:url(:/img/C:/Users/Administrator/Desktop/下载.jpg);}");

    //给按钮添加样式
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/img/C:/Users/Administrator/Desktop/下载.jpg);}"
                                  "QPushButton:hover{border-image:url(:/img/C:/Users/Administrator/Desktop/bug.jpg)}"
                                  "QPushButton:pressed{border-image:url(:/img/C:/Users/Administrator/Desktop/Luffy.png)}");
}

Widget::~Widget()
{
    delete ui;
}
