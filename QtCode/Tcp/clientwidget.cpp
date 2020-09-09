#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle("客户端");

    tcpSocket = NULL;

    //分配空间，指定父对象
    tcpSocket = new QTcpSocket(this);

    //客户端连接成功
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        ui->textEditRead->setText("客户端成功和服务器建立好连接");
    });

    //读数据
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //获取对方发送的内容
        QByteArray arr = tcpSocket->readAll();
        //追加到编辑区中
        ui->textEditRead->append(arr);
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //从行编辑区获取输入的服务器ip和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);

}

void ClientWidget::on_buttonSend_clicked()
{
    //获取编辑区内容
    QString content = ui->textEditWrite->toPlainText();

    //给对方发送数据
    tcpSocket->write(content.toUtf8().data());
}

void ClientWidget::on_buttonClose_clicked()
{
    //tcp主动和服务端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
