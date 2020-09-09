#include "mywidget.h"
#include "ui_mywidget.h"

#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    timerId = this->startTimer(1000);//以毫秒为单位，每隔1s触发一次

    timerId2 = this->startTimer(500);

    connect(ui->pushButton,&MyButton::clicked,[=](){
        qDebug() << "按钮被按下";
    });

    //安装过滤器
    ui->label2->installEventFilter(this);

    //鼠标追踪
    ui->label2->setMouseTracking(true);

}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *e){
    qDebug() << (int)e->key();
}

void MyWidget::timerEvent(QTimerEvent *e){
    if(this->timerId == e->timerId()){
        static int sec = 0;
        ui->label->setText(QString("<center><h1>Time1:%1</h1></center>").arg(++sec));

        if(sec==5){
            //停止定时器
            this->killTimer(this->timerId);
        }

    }else if(e->timerId() == this->timerId2){
        static int sec = 0;
        ui->label2->setText(QString("<center><h1>Time2:%1</h1></center>").arg(++sec));
    }


}

void MyWidget::mousePressEvent(QMouseEvent *e){
    qDebug() << "=======================";
}

void MyWidget::closeEvent(QCloseEvent *e){
     int returnVal = QMessageBox::question(this,"question","确认关闭窗口吗?");
     if(returnVal == QMessageBox::Yes){
         //关闭窗口
         //处理关闭窗口事件，接收事件，事件不再下传
         e->accept();
     }else{
         //忽略事件，继续给父组件传递
         e->ignore();
     }
}

bool MyWidget::event(QEvent *event){
    //事件分发
    if(event->type() == QEvent::Timer){
        //禁用定时器
        //如果返回true，则事件停止传播
        //QTimeEvent *e

//        QTimerEvent * e = static_cast<QTimerEvent *>(event);
//        this->timerEvent(e);

        return true;
    }else if(event->type() == QEvent::KeyPress){
        //类型转换
        QKeyEvent *e = static_cast<QKeyEvent *>(event);
        if(e->key() == Qt::Key_B){
            return QWidget::event(e);
        }else{
            //不做任何处理
            return true;
        }
    }else{
        //事件下传，交给基类处理
        return QWidget::event(event);
    }
}


bool MyWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->label2){
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        //判断事件
        if(event->type() == QEvent::MouseMove){
            ui->label2->setText(QString("<center><h1>Mouse Move:(%1,%2)</h1></center>").arg(e->x(),e->y()));
            return true;
        }else if(event->type() == QEvent::MouseButtonPress){
            ui->label2->setText(QString("<center><h1>Mouse Button Press:(%1,%2)</h1></center>").arg(e->x(),e->y()));
            return true;
        }else if(event->type() == QEvent::MouseButtonRelease){
            ui->label2->setText(QString("<center><h1>Mouse Button Release:(%1,%2)</h1></center>").arg(e->x(),e->y()));
            return true;
        }else {
            //下传
            return QWidget::eventFilter(watched,event);
        }
    }
}
