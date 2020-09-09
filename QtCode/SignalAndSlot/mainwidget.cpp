#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>//打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)//调用父类构造方法，完成子类的初始化
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100,100);

    b2 = new QPushButton(this);
    b2->setText("abc");

    //重新设置窗口的大小
    resize(400,300);

    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);
    /*
        &b1:信号发出者，指针类型
        &QPushButton::pressed:处理的信号，&发送者的类名::信号名字
        this:信号的接收者
        &MainWidget::close:槽函数，信号处理函数 接受者的类名::槽函数名字
    */

    /*
        自定义槽，普通函数的用法
        Qt5:任意的成员函数，普通全局函数，静态函数
        槽函数需要和信号一致（参数，返回值）
        由于信号都是没有返回值，所以槽函数也没有返回值
    */

    connect(b2,&QPushButton::released,this,&MainWidget::mySlot);
    connect(b2,&QPushButton::released,&b1,&QPushButton::hide);

    /*
        信号:短信
        槽函数:接收短信的手机
    */

    setWindowTitle("老大");
//    this->setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50,50);

    //显示子窗口
    //w.show();

    //b3释放时，切换窗口
    connect(&b3,&QPushButton::released,this,&MainWidget::changeWin);

    //处理子窗口的信号

    //定义函数指针，指定具体的重载函数
    //指定无参的重载函数
    void (SubWidget::*funSignal)() = &SubWidget::mySignal;

    connect(&subWin,funSignal,this,&MainWidget::dealSub);

    //指定有参的重载函数
    void (SubWidget::*testSignal)(int,QString) = &SubWidget::mySignal;

    connect(&subWin,testSignal,this,&MainWidget::dealSlot);

    //Lambda表达式，匿名函数对象
    //qt配合信号一起使用，非常方便

    QPushButton *b4 = new QPushButton(this);
    b4->setText("Lambda表达式");
    b4->move(150,150);


    connect(b4,&QPushButton::clicked,[=](bool
             isCheck)
            //= :把外部所有局部变量，类中所有成员以值的方式传入
            //this:类中所有成员以值传递
            //&:把外部所有局部变量，引用符号
    {
        qDebug() << isCheck;//false
    });

}


void MainWidget::mySlot(){
    b2->setText("123");
}

MainWidget::~MainWidget()
{

}


void MainWidget::changeWin(){
    //本窗口隐藏
    this->hide();
    //子窗口显示
    subWin.show();
}

void MainWidget::dealSub(){
    //父窗口显示
    this->show();
    //子窗口隐藏
    subWin.hide();
}

void MainWidget::dealSlot(int a,QString str){
    qDebug() << a << str.toUtf8().data();
}
