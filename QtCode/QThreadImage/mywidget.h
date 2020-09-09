#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include "mythread.h"

#include <QThread>
#include <QPushButton>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

    //接收图片的槽函数
    void recvImage(QImage image);

    //释放资源
    void closeResource();

private:
    Ui::MyWidget *ui;

    QImage img;
    MyThread *mt;//自定义线程
    QThread *thread;
};

#endif // MYWIDGET_H
