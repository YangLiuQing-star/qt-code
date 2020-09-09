#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QMatrix>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnCircle_clicked();

    void on_btnSmaller_clicked();

    void on_btnLarge_clicked();

private:
    Ui::MyWidget *ui;

    QTimer *myTimer;//声明定时器
    QPixmap *pixmap;//声明图片

    int width;//图片的宽
    int height;//图片的高
};

#endif // MYWIDGET_H
