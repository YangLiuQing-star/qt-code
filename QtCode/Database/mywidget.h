#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>

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
    void on_buttonDel_clicked();

    void on_buttonSure_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
