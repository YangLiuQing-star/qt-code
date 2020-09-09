#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::drawImage(){
    //定义绘图设备
    QImage img = QImage(500,500,QImage::Format_ARGB32);
    //定义画家，指定绘图设备
    QPainter p(&img);


    //定义画笔对象
    QPen pen;
    pen.setWidth(5);//设置宽度
    //把画笔交给画家
    p.setPen(pen);

    //定义画刷
    QBrush brush;
    brush.setStyle(Qt::FDiagPattern);
    brush.setColor(Qt::red);
    p.setBrush(brush);


    //定义五个点
    QPoint points[] = {
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500)
    };

    p.drawPolygon(points,5);

    //通过信号发送图片
    emit sendImage(img);
}
