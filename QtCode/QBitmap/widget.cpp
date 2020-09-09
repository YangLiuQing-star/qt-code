#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QBitmap>

/*
    绘图设备
    QPixmap:针对屏幕进行优化了和平台无关，不能对图片进行修改
    QImage:和平台无关，可以对图片进行修改，在线程中绘图
    QPicture:保存绘图的状态（以二进制文件形式）
*/
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    //指定画家，操作的对象是当前窗口
    QPainter p(this);
    //QPixmap图片背景透明
    p.drawPixmap(0,0,QPixmap("../Image/butterfly.png"));
    //QBitmap图片背景不透明
    p.drawPixmap(200,0,QBitmap("../Image/butterfly.png"));

    //图片背景白色
    QPixmap pixmap;
    pixmap.load("../Image/butterfly1.png");
    p.drawPixmap(0,160,pixmap);

    //QBitmap 图片背景白色
    QBitmap bitmap;
    bitmap.load("../Image/butterfly1.png");
    p.drawPixmap(200,160,bitmap);
}
