#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    //线程处理函数
    void myTimeOut();

    //设置标志位
    void setFlag(bool isStop = false);

private:
	//是否终止循环的标志位
    bool isStop;

signals:
    void mySignal();

public slots:
};

#endif // MYTHREAD_H
