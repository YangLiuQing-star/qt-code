#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>

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
    void on_buttonAdd_clicked();

    void on_buttonCancel_clicked();

    void on_buttonDel_clicked();

    void on_buttonFind_clicked();

    void on_buttonCertain_clicked();

private:
    Ui::MyWidget *ui;

    QSqlTableModel *model;
};

#endif // MYWIDGET_H
