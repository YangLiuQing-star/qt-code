#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>

#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    void enterEvent(QEvent *ev);
    void leaveEvent(QEvent *ev);

signals:

public slots:
};

#endif // MYLABEL_H
