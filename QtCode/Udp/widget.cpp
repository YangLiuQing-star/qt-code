#include "widget.h"
#include "ui_widget.h"

#include <QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("服务器端口为:8888");

    //分配空间，指定父对象，方便回收
    udpSocket = new QUdpSocket(this);

    //绑定端口（如果添入某个组播，必须指定IP为ipv4）
//    udpSocket->bind(8888);
    udpSocket->bind(QHostAddress::AnyIPv4,8888);

    //加入某个组播
    //组播地址为D类地址，必须使用ipv4
    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2"));

//    udpSocket->leaveMulticastGroup();//退出组播

    //当对方成功发送数据，自动触发readyRead
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::dealMsg);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealMsg(){
    char buf[1024] = {0};
    QHostAddress cliAddr;//对方地址
    quint16 port;//对方端口
    //读取对方发送的内容，IP，port
    qint64 len = udpSocket->readDatagram(buf,sizeof(buf),&cliAddr,&port);

    if(len > 0){
        QString str = QString("[%1:%2]: %3")
                .arg(cliAddr.toString())
                .arg(port)
                .arg(buf);
        //设置编辑区的内容
        ui->textEdit->setText(str);
    }
}

void Widget::on_buttonSend_clicked()
{
    //从窗口的行编辑区，获取对方的IP和端口
    QString ip = ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //获取编辑器的内容
    QString content = ui->textEdit->toPlainText();
    //给指定的IP发送数据
    udpSocket->writeDatagram(content.toUtf8(),QHostAddress(ip),port);
}
