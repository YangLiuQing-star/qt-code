#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB();//连接数据库

    void init();//初始化

private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_cbFactory_currentIndexChanged(const QString &arg1);

    void on_cbBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_btCertain_clicked();

    void on_btCancel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
