#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //调用读和写函数
    this->readData();
    this->writeData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readData(){
    QFile file;
    file.setFileName("../demo.txt");

    bool isOk = file.open(QIODevice::ReadOnly);

    if(isOk == true){
        QTextStream ts(&file);
        QString str;
        int a;
        //设置编码方式
        ts.setCodec("UTF-8");
        ts >> str >> a;

        qDebug() << str.toUtf8().data() << a;
    }

    file.close();

}

void Widget::writeData(){
    QFile file;
    file.setFileName("../demo.txt");

    bool isOk = file.open(QIODevice::WriteOnly);

    if(isOk == true){
        QTextStream ts(&file);
        //指定编码方式
        ts.setCodec("UTF-8");
        ts << QString("主要看气质") << 250;
    }

    file.close();
}


void Widget::on_pushButton_clicked()
{
    //打开文件对话框
    QString path = QFileDialog::getOpenFileName(this,"open","../");

    if(path.isEmpty() == false){
        QFile file;
        file.setFileName(path);

        bool isOk = file.open(QIODevice::ReadOnly);

        if(isOk == true){//打开成功
            QTextStream ts(&file);
            QString str;
            //设置编码方式
            ts.setCodec("UTF-8");

            //读所有
            str = ts.readAll();

            ui->textEdit->setText(str);
        }

        file.close();
    }
}
