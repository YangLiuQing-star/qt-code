#include "mybutton.h"
#include <QDebug>

//自定义按钮，继承于QPushButton
MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

MyButton::~MyButton(){
    qDebug() << "按钮被析构";
}
