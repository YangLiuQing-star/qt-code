#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QPen>
#include <QBrush>


class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    //线程处理函数
    void drawImage();

signals:
    void sendImage(QImage img);//信号函数

public slots:
};

#endif // MYTHREAD_H
