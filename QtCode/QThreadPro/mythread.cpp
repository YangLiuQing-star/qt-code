#include "mythread.h"

#include <QDebug>
#include <QMessageBox>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    //是否终止循环
    isStop = false;
}

void MyThread::myTimeOut(){
    while(isStop == false){
        //每隔1秒发送一个信号
        QThread::sleep(5);
        emit mySignal();

//        QMessageBox::aboutQt(NULL);

        qDebug() << "子线程号--->" << QThread::currentThread();
    }
}

void MyThread::setFlag(bool isStop){
    this->isStop = isStop;
}
