#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYBUTTON_H
