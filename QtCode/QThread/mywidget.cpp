#include "mywidget.h"
#include "ui_mywidget.h"


MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //创建定时器
    myTimer = new QTimer(this);

    connect(myTimer,&QTimer::timeout,this,&MyWidget::dealTimerout);

    //分配空间
    thread = new MyThread(this);

    //发射信号
    connect(thread,&MyThread::isDone,this,&MyWidget::dealDone);

    //关闭窗口触发关闭线程的槽函数
    connect(this,&MyWidget::destroyed,this,&MyWidget::closeThread);
}

MyWidget::~MyWidget()
{
    delete ui;
    delete thread;
}

void MyWidget::dealTimerout(){
    static int i = 0;
    i++;
    //设置lcd的值
    ui->lcdNumber->display(i);
}

void MyWidget::on_pushButton_clicked()
{
    //如果定时器没有激活
    if(myTimer->isActive() == false){
        //启动定时器
        myTimer->start(1000);
    }

    //启动线程，处理数据
    thread->start();


}

void MyWidget::dealDone(){
    qDebug() << "数据处理完毕";

    //关闭定时器
    myTimer->stop();
}

void MyWidget::closeThread(){
    //退出线程
    thread->quit();

    //等待线程处理完手头的工作
    thread->wait();
}
