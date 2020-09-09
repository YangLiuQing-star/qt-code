#include "mywidget.h"

#include "mybutton.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    /*
        对于父窗口（主窗口），坐标系统相对于屏幕而言
        原点：相对于屏幕左上角
        x:往右递增
        y:往下递增
    */
    move(100,100);
    QPushButton *b1 = new QPushButton(this);
    b1->move(100,100);
    b1->setText("^_^");
    b1->resize(100,100);

    QPushButton *b2 = new QPushButton(b1);
    b2->move(10,10);
    b2->setText("@_@");

    QPushButton *b3 = new MyButton(this);
    b3->setText("自定义按钮");

    //1.指定父对象之后 2.直接或者间接继承于QObject
    //子对象如果是动态分配空间的new，不需要手动释放delete
    //系统会自动回收
}

MyWidget::~MyWidget()
{

}
