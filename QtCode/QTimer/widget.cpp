#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建定时器对象
    myTimer = new QTimer(this);

    connect(myTimer,&QTimer::timeout,[=](){
        static int i = 0;
        i++;
        ui->lcdNumber->display(i);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonStart_clicked()
{
    if(myTimer->isActive() == false){//如果定时器未启动
        //启动定时器，时间间隔为100ms，每隔100ms定时器自动触发timeout
        myTimer->start(100);
    }
}

void Widget::on_buttonStop_clicked()
{
    if(myTimer->isActive() == true){//如果定时器启动，关闭
        //关闭定时器
        myTimer->stop();
    }
}
