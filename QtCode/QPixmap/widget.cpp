#include "widget.h"
#include "ui_widget.h"


#include <QPainter>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    //绘图设备，400*300
    QPixmap pixmap(400,300);
    //指定绘图设备
    QPainter p(&pixmap);
    //填充背景
    //p.fillRect(0,0,400,300,QBrush(QBrush::white));
    pixmap.fill(Qt::white);

    p.drawPixmap(0,0,80,80,QPixmap("../Image/face.png"));
    //保存图片
    pixmap.save("../pixmap.png");
}

Widget::~Widget()
{
    delete ui;
}
