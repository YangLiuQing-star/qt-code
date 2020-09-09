#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT//使用信号与槽的时候需要

public:
	//构造函数
    MyWidget(QWidget *parent = 0);
    //析构函数
    ~MyWidget();
};

#endif // MYWIDGET_H
