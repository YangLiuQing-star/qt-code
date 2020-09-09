#include "mylabel.h"

#include <QLabel>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

void MyLabel::mousePressEvent(QMouseEvent *ev){
    int i = ev->x();
    int j = ev->y();

    if(ev->button() == Qt::LeftButton){//按鼠标左键
        qDebug() << "left";
    }else if(ev->button() == Qt::RightButton){
        qDebug() << "right";
    }else if(ev->button() == Qt::MidButton){
        qDebug() << "mid";
    }

    /*
        QString str = QString("abc %1 ^_^ %2").arg(123).arg("make");
        str = abc 123 ^_^ make
    */
    QString text = QString("<center><h1>Mouse Press:(%1,%2)</h1></center>")
            .arg(i).arg(j);

    this->setText(text);

}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev){
    QString text = QString("<center><h1>Mouse Release:(%1,%2)</h1></center>")
            .arg(ev->x()).arg(ev->y());

    this->setText(text);

}

void MyLabel::mouseMoveEvent(QMouseEvent *ev){
    QString text = QString("<center><h1>Mouse Move:(%1,%2)</h1></center>")
            .arg(ev->x()).arg(ev->y());

    //this->setText(text);
}

void MyLabel::enterEvent(QEvent *ev){
    QString text = QString("<center><h1>Mouse Enter:</h1></center>");

    this->setText(text);
}

void MyLabel::leaveEvent(QEvent *ev){
    QString text = QString("<center><h1>Mouse Leave:</h1></center>");

    this->setText(text);
}
