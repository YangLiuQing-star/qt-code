#include "mywidget.h"
#include "ui_mywidget.h"

/*
    图片播放器
*/
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myTimer = new QTimer;
    pixmap = new QPixmap;

    connect(myTimer,&QTimer::timeout,[=](){
        static int i = 1;
        QString filePath = QString(":/girl/girl%1.jpg").arg(i);
        pixmap->load(filePath);
        //qDebug() << filePath;
        //初始化图片的宽高
        width = pixmap->width();
        height = pixmap->height();
        ui->label->setPixmap(*pixmap);
        ui->label->setScaledContents(true);
        i++;
        if(i == 10){
            i = 1;
        }
    });
}

MyWidget::~MyWidget()
{
    delete ui;
    delete myTimer;
    delete pixmap;
}

void MyWidget::on_btnStart_clicked()
{
    if(myTimer->isActive() == false){
        //启动定时器，定时时间1秒
        myTimer->start(1000);
    }
}

void MyWidget::on_btnStop_clicked()
{
    if(myTimer->isActive() == true){
        myTimer->stop();
    }
}

void MyWidget::on_btnCircle_clicked()
{
    QMatrix matrix;
    //设置旋转的角度
    matrix.rotate(90);
    *pixmap = pixmap->transformed(matrix);
    ui->label->setPixmap(*pixmap);
}

void MyWidget::on_btnSmaller_clicked()
{
    width = width/2;
    height = height/2;
    *pixmap = pixmap->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label->setPixmap(*pixmap);
    ui->label->setScaledContents(false);
}

void MyWidget::on_btnLarge_clicked()
{
    width *= 2;
    height = height*2;
    *pixmap = pixmap->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label->setPixmap(*pixmap);
    ui->label->setScaledContents(false);
}
