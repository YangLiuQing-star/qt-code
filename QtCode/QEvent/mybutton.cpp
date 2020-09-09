#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        qDebug() << "按下的是鼠标左键";
        //事件接收后，就不会往下传递

        e->ignore();//忽略，事件下传，事件传递给了父组件，不是给父类（基类）
    }else{
        //不做处理
        //事件的忽略，事件继续下传
        QPushButton::mousePressEvent(e);
    }
//    QPushButton::mousePressEvent(e);

}
