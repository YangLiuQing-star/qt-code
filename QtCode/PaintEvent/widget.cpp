#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
//    QPainter p(this);
    QPainter p;//创建画家对象

    p.begin(this);//指定当前窗口为绘图设备

    //绘图操作
    //画背景图
    //p.drawPixmap(0,0,this->width(),this->height(),QPixmap("../Image/Luffy.png"));

    //绘制矩形
//    p.drawPixmap(this->rect(),QPixmap("../Image/Luffy.png"));

    //定义画笔
    QPen pen;

    //定义画刷
    QBrush brush;

    //设置画刷颜色
    brush.setColor(Qt::red);
    //设置画刷样式
    brush.setStyle(Qt::Dense1Pattern);

    //把画刷交给画家
    p.setBrush(brush);

    //设置画笔的线框宽度
    pen.setWidth(5);
    //设置画笔的颜色
//    pen.setColor(Qt::red);

    //rgb设置颜色
    pen.setColor(QColor(14,9,234));
    //设置样式
    pen.setStyle(Qt::DashLine);
    //把画笔交给画家
    p.setPen(pen);


    //画家画直线
    p.drawLine(50,50,150,50);
    p.drawLine(50,50,50,150);

    //画家画矩形
    p.drawRect(150,150,100,50);

    //画家画圆形
    p.drawEllipse(QPoint(150,150),50,25);

    //画家画笑脸
    p.drawPixmap(this->x,200,80,80,QPixmap("../Image/face.png"));

    p.end();
}

void Widget::on_pushButton_clicked()
{
    //位置每次移动20个单位
    this->x += 20;
    //位置超出边框的宽度，从头开始移动
    if(x > this->width()){
        x = 0;
    }

    //刷新窗口，让窗口重绘，整个窗口都刷新
    this->update();//间接调用paintEvent
}
