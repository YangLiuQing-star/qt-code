#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QFileDialog>
#include <QTextEdit>
#include <QFileInfo>
#include <QDebug>

#include <QDateTime>
#include <QDataStream>//数据流


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//读文件
void Widget::on_buttonRead_clicked()
{
    //打开文件对话框
    QString path = QFileDialog::getOpenFileName(this,"open",
                                                "../","TXT(*.txt)");

    if(path.isEmpty() == false){
        //创建文件对象
        QFile file(path);

        //打开文件，只读方式打开
        bool isOk = file.open(QIODevice::ReadOnly);
        if(isOk == true){
//            //读文件，默认只支持utf8编码，否则会乱码
//            QByteArray arr = file.readAll();
//            //显示到编辑区
////            ui->textEdit->setText(QString(arr));
//            ui->textEdit->setText(arr);


            QByteArray arr;
            while(file.atEnd() == false){//如果没有到达文件末尾
                //读一行
                arr += file.readLine();
            }
            ui->textEdit->setText(arr);
        }

        //关闭文件
        file.close();

        //获取文件信息
        QFileInfo info(path);
        qDebug() << "文件名字:" << info.fileName().toUtf8().data();
        qDebug() << "文件后缀:" << info.suffix();
        qDebug() << "文件大小:" << info.size();
        qDebug() << "文件创建时间:" << info.created().
                    toString("yyyy-MM-dd hh:mm:ss");
    }
}

//写内容到文件
void Widget::on_buttonWrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if(path.isEmpty() == false){
        //先创建文件对象
        QFile file;
        //关联文件名字
        file.setFileName(path);

        //打开文件
        bool isOk = file.open(QIODevice::WriteOnly);

        if(isOk == true){
            //获取编辑区的内容
            QString str = ui->textEdit->toPlainText();
            //将内容写入文件中，QString --->QByteArray
            file.write(str.toUtf8());

            //QString ---> C++ string --->char *
//            file.write(str.toStdString().data());

            //QString ---> QByteArray
//            QString str2 = "123";
//            QByteArray a = str2.toUtf8();//中文
//            a = str2.toLocal8Bit();//本地平台编码

            //QByteArray ---> char*
//            char *b = a.data();

            //char * ---> QString
//            char *ch = "abc";
//            QString str3 = QString(ch);

        }
        //关闭文件
        file.close();
    }
}
