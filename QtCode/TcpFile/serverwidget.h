#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QTimer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

    void sendData();//发送数据

private slots:
    void on_buttonSelect_clicked();

    void on_buttonSend_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer;//通信监听
    QTcpSocket *tcpSocket;//通信套接字

    QFile file;//文件对象
    QString fileName;//文件名
    qint64 fileSize;//文件大小

    qint64 sendSize;//已发送文件的大小

    QTimer timer;//定时器
};

#endif // SERVERWIDGET_H
