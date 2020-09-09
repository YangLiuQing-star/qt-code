#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

//绘制复杂图形
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //1.去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //2.把窗口背景设置为透明
    this->setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

/*重写绘图事件*/
void Widget::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawPixmap(0,0,QPixmap("../Image/sunny.png"));

}

/*重写鼠标移动事件*/
void Widget::mouseMoveEvent(QMouseEvent *e){
    if(e->buttons() & Qt::LeftButton){
        this->move(e->globalPos() - p);
    }

}

//重写鼠标按下事件
void Widget::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){//鼠标右键按下
        //关闭窗口
        this->close();
    }else if(e->button() == Qt::LeftButton){//鼠标左键按下
        //求坐标差值:当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }

}
