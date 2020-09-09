#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPicture>
#include <QImage>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPicture picture;
    QPainter p;
    p.begin(&picture);

    //画图
    p.drawPixmap(0,0,80,80,QPixmap("../Image/face.png"));
    //画直线
    p.drawLine(50,50,180,50);

    p.end();

    //保存的是二进制文件
    picture.save("../pf.png");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){

#if 0
    QPicture pic;
    //加载文件
    pic.load("../pf.png");
    QPainter p(this);
    p.drawPicture(0,0,pic);
#endif
    QPixmap pixmap;
    pixmap.load("../Image/face.png");
    QPainter p(this);

    //QPixmap转化为QImage
    QImage tmpImg = pixmap.toImage();
    p.drawImage(0,0,tmpImg);

    QImage img;
    img.load("../Image/face.png");
    //QImage--->QPixmap
    QPixmap tmpPixmap = QPixmap::fromImage(img);
    p.drawPixmap(150,0,tmpPixmap);


}
