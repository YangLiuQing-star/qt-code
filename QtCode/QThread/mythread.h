#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QThread//自定义线程类，继承线程类的基类QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start函数间接调用
    void run();


signals:
    void isDone();

public slots:
};

#endif // MYTHREAD_H
