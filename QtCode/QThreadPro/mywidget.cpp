#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //动态分配空间，不能指定父对象
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义线程加入到子线程中
    myT->moveToThread(thread);

    connect(this,&MyWidget::startThread,myT,&MyThread::myTimeOut);

    connect(myT,&MyThread::mySignal,this,&MyWidget::dealSignal);

    qDebug() << "主线程号--->" << QThread::currentThread();

    connect(this,&MyWidget::destroyed,this,&MyWidget::dealDestroyed);

    //线程处理函数内部，不允许操作图形界面

    //connect()第五个参数的作用，多线程才有意义，连接方式:默认，队列，直接
    //如果是多线程，默认使用队列
    //如果是单线程，默认使用直接方式

}

MyWidget::~MyWidget()
{
    delete ui;
}



void MyWidget::dealDestroyed(){
    on_buttonClose_clicked();
}

void MyWidget::on_buttonStart_clicked()
{

    if(thread->isRunning() == true){//线程正在运行，直接返回
        return;
    }

    //启动线程，但是没有调用线程处理函数
    thread->start();
    //不能直接调用线程处理函数
    //直接调用将导致线程处理函数和主线程是在同一个线程

    //方便暂停和开始
    myT->setFlag(false);

    //myT->myTimeOut();

    //只能通过信号和槽来调用
    //发送启动线程信号
    emit startThread();
}

void MyWidget::dealSignal(){
    static int count = 0;
    count++;
    ui->lcdNumber->display(count);
}

void MyWidget::on_buttonClose_clicked()
{
    if(thread->isRunning() == true){
        myT->setFlag(true);
        thread->quit();
        thread->wait();
    }
    delete myT;
}
