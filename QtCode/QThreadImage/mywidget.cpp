#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //创建线程对象
    mt = new MyThread;
    //创建子线程
    thread = new QThread(this);
    //加入到子线程
    mt->moveToThread(thread);
    //开启子线程，并不会调用线程函数
    thread->start();

    //使用信号槽开启线程，画图开始
    connect(ui->pushButton,&QPushButton::pressed,mt,&MyThread::drawImage);

    //画图完成后，发射信号，处理信号
    connect(mt,&MyThread::sendImage,this,&MyWidget::recvImage);

    connect(this,&MyWidget::destroyed,this,&MyWidget::closeResource);
}

MyWidget::~MyWidget()
{
    delete ui;
}

//在窗口绘图，需要重写paintEvent函数
void MyWidget::paintEvent(QPaintEvent *){
    //定义画家，指定绘图设备为窗口
    QPainter p(this);
    p.drawImage(50,50,img);
}

void MyWidget::recvImage(QImage image){
    img = image;
    //更新窗口，间接调用paintEvent
    update();
}

//释放资源
void MyWidget::closeResource(){
    delete mt;
    thread->quit();
    thread->wait();
}


