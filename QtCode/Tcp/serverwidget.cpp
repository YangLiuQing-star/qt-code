#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    setWindowTitle("服务器:8888");

    //初始化
    tcpServer = NULL;
    tcpSocket = NULL;

    //指定父对象，让其自动回收空间
    this->tcpServer = new QTcpServer(this);

    //监听任意主机下的8888端口
    tcpServer->listen(QHostAddress::Any,8888);

    //建立连接
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的套接字
        tcpSocket = this->tcpServer->nextPendingConnection();

        //获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        QString str = QString("[%1,%2]:成功连接").arg(ip).arg(port);

        ui->textEditRead->setText(str);


        //从套接字中读数据
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //从通信套接字中取出内容
            QByteArray arr = tcpSocket->readAll();
            //追加
            ui->textEditRead->append(arr);
        });
    });


}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonSend_clicked()
{

    if(NULL == tcpSocket){
        return;
    }

    //获取编辑区的内容
    QString str = ui->textEditWrite->toPlainText();

    //给对方发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_buttonClose_clicked()
{
    if(NULL == tcpSocket){
        return;
    }

    //tcp主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}
