#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle("客户端");

    isStart = true;

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //取出接收的数据
        QByteArray buf = tcpSocket->readAll();


        if(isStart == true){//接收头
            //置为false
            isStart = false;
            //解析头信息 "hello##1024"
            //初始化，字符串分割
            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",0,1).toInt();
            recvSize = 0;
            //打开文件
            file.setFileName(fileName);
            bool isOk = file.open(QIODevice::WriteOnly);
            if(isOk == false){
                qDebug() << "文件打开失败...";
                return;//打开文件失败，直接返回
            }

            QString str = QString("接收的文件:[%1:%2kb]").arg(fileName).arg(fileSize/1024);
            QMessageBox::information(this,"文件信息",str);
            //设置进度条
            ui->progressBar->setMaximum(fileSize/1024);//最大值
            ui->progressBar->setMinimum(0);//最小值
            ui->progressBar->setValue(0);//当前值


        }else{//接收文件信息
            qint64 len = file.write(buf);
            while(len > 0){
                recvSize += len;
                //把数子转化成QString
                QString str = QString::number(recvSize);
                tcpSocket->write(str.toUtf8().data());

            if(recvSize == fileSize){
                //先给服务器发送（接收文件完成的信息）
                tcpSocket->write("file done");
                QMessageBox::information(this,"提示信息","文件接收完成...");
                //断开连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
                file.close();
             }

                //更新进度条
                ui->progressBar->setValue(recvSize/1024);
                qDebug() <<"客户端---->" << str;
            }
        }
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //从编辑区，获取服务器的IP和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}
