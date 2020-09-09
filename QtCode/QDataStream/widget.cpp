#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>

#define cout qDebug() << "{" << __FILE__ << ":" << __LINE__ << "}"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //使用QDataStream进行读写操作
    writeData();
    readData();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::writeData(){
    //创建文件对象
    QFile file("../data.txt");

    //打开文件，以只写方式打开
    bool isOk = file.open(QIODevice::WriteOnly);

    if(isOk == true){
        //创建数据流和file文件关联
        //往数据流中写数据，相当于往文件里写数据
        QDataStream stream(&file);
        //输出内容
        stream << QString("主要看气质") << 250;

        file.close();
    }
}


void Widget::readData(){
    //创建文件对象
    QFile file("../data.txt");

    //打开文件，以只读方式打开
    bool isOk = file.open(QIODevice::ReadOnly);

    if(isOk == true){
        //创建数据流和file文件关联
        //往数据流中读数据，相当于往文件里读数据
        QDataStream stream(&file);

        //读的时候，按照写的顺序取数据
        QString str;
        int a;
        //从文件中读取内容
        stream >> str >> a;

        //输出结果
//        qDebug() << str << a;
        cout << str << a;

        file.close();
    }
}
