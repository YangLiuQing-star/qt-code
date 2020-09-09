#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>

#include <QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;//通信套接字

    QFile file;//文件对象
    QString fileName;//文件名
    qint64 fileSize;//文件大小

    qint64 recvSize;//已接收文件的大小

    bool isStart;//标志头信息是否开始传输
};

#endif // CLIENTWIDGET_H
