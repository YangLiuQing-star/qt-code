#include "widget.h"
#include "ui_widget.h"

#include <QBuffer>//内存文件
#include <QDebug>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建字节数组用来保存
    QByteArray arr;
    QBuffer memFile(&arr);//创建内存文件

    memFile.open(QIODevice::WriteOnly);
    memFile.write("111111111");
    memFile.write("2222222222222222");

    memFile.close();

    qDebug() << memFile.buffer();
    qDebug() <<"QByteArray: " << arr;



    QBuffer memFile2;
    memFile2.open(QIODevice::WriteOnly);
    QDataStream stream(&memFile2);
    //写数据
    stream << QString("西游记，水浒传，红楼梦，三国演义") << 250;
    memFile2.close();

    qDebug() << memFile2.buffer();

    memFile2.open(QIODevice::ReadOnly);
    stream.setDevice(&memFile2);
    QString str;
    int a;
    stream >> str >> a;
    memFile2.close();

    qDebug() << str.toUtf8().data() << a;
}

Widget::~Widget()
{
    delete ui;
}
