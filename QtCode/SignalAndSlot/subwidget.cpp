#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");

    resize(400,300);

    //按钮触发一个中断
    connect(&b,&QPushButton::clicked,this,&SubWidget::sendSlot);
}

void SubWidget::sendSlot(){
    emit mySignal();
    emit mySignal(250,"我是子窗口");
}
