#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QKeyEvent>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    int timerId;
    int timerId2;

private:
    Ui::MyWidget *ui;

protected:
    void keyPressEvent(QKeyEvent *e);

    void timerEvent(QTimerEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void closeEvent(QCloseEvent *e);

    bool event(QEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MYWIDGET_H
