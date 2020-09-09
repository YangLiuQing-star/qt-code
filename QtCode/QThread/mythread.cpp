#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    //复杂的数据处理
    //需要耗时5s
    sleep(5);

    //发射信号
    emit isDone();
}
