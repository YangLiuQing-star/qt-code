#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


#include <QFile>
#include <QFileDialog>
#include <QTextEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
	//定义槽函数
    void on_buttonRead_clicked();

    void on_buttonWrite_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
