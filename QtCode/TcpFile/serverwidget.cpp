#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器端口为:8888");

    //创建监听
    tcpServer = new QTcpServer(this);
    //监听8888端口
    tcpServer->listen(QHostAddress::Any,8888);

    //禁用两个按钮都不能按
    ui->buttonSelect->setEnabled(false);
    ui->buttonSend->setEnabled(false);

    //如果客户端成功和服务端连接
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //获取建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //使用套接字，获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        QString str = QString("[%1,%2]成功连接").arg(ip).arg(port);
        //在编辑区显示
        ui->textEdit->setText(str);

        //成功连接后，启用选择按钮，选择文件
        ui->buttonSelect->setEnabled(true);

        //服务器接收客户端的反馈信息
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //获取客户端信息
            QByteArray arr = tcpSocket->readAll();
            QString str = QString(arr);

            if(str == "file done"){//文件接收完毕
                ui->textEdit->append("文件发送完毕");

                //断开与客户端的连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();

                //关闭文件
                file.close();
            }else{
                qDebug() <<"服务器---->" << arr;
            }
        });

    });

    //进行读写操作
    connect(&timer,&QTimer::timeout,[=](){
        //关闭定时器
        timer.stop();
        //发送真正的文件信息
        sendData();
    });

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//选择文件的按钮
void ServerWidget::on_buttonSelect_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");

    if(filePath.isEmpty() == false){//如果选择文件路径有效
        //初始化
        fileName.clear();
        fileSize = 0;
        sendSize = 0;
        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();

        //只读方式打开文件
        file.setFileName(filePath);
        bool isOk = file.open(QIODevice::ReadOnly);

        if(isOk == false){//打开失败
            qDebug() << "文件打开失败";
        }

        //提示
        ui->textEdit->append(filePath);

        //禁用选择按钮，启用发送按钮
        ui->buttonSelect->setEnabled(false);
        ui->buttonSend->setEnabled(true);

    }else{
        qDebug() << "选择文件路径出错";
    }
}

void ServerWidget::on_buttonSend_clicked()
{
    //先发送文件头信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8());
    if(len > 0){
        //头部信息发送成功
        //防止Tcp粘包文件，需要通过定时器延时20ms，20ms后在发送文件数据
        timer.start(20);
    }else{
        qDebug() << "头部信息发送失败";
        file.close();
        ui->buttonSelect->setEnabled(true);
        ui->buttonSend->setEnabled(false);
    }

}

void ServerWidget::sendData(){
    qint64 len = 0;
    do{
        len = 0;
        //每次读取4字节
        char buf[1024*4] = {0};
        //从文件中读数据，加入到buf中
        len = file.read(buf,sizeof(buf));
        //发送数据
        len = tcpSocket->write(buf,len);

        //发送的数据需要累加
        sendSize += len;
    }while(len > 0);

    //判断是否发送文件完毕
    if(sendSize == fileSize){
        ui->textEdit->append("文件发送完毕");
        file.close();

        //把客户端关闭，断开连接
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
}
