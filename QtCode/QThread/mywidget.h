#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "mythread.h"
#include <QWidget>

#include <QTimer>//定时器头文件
#include <QThread>//线程基类
#include <QDebug>


/*
 *  多线程
 *  1.自定义一个类，继承QThread
 *  2.重写线程处理函数run
 *  3.启动线程start，间接调用run函数
 */
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealTimerout();//定时器槽函数

    void dealDone();//处理线程的槽函数

    void closeThread();//关闭线程的槽函数

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyWidget *ui;

    QTimer *myTimer;//声明变量

    MyThread *thread;//聚合自定义线程

};

#endif // MYWIDGET_H
