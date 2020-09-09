#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QImage>
#include <QColor>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建一个绘图设备，QImage::Format_ARGB32:背景透明
    QImage image(400,300,QImage::Format_ARGB32);
    //指定绘图设备
    QPainter p;
    p.begin(&image);
    //绘图
    p.drawImage(0,0,QImage("../Image/face.png"));

    //操作像素点
    for(int i = 0;i < 50;i++){
        for(int j = 0;j < 50;j++){
            image.setPixel(QPoint(i,j),qRgb(0,255,0));
        }
    }

    //保存图片
    image.save("../qImg.png");

    p.end();
}

Widget::~Widget()
{
    delete ui;
}
