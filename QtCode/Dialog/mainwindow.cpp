#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *mBar =  menuBar();
    setMenuBar(mBar);
    //添加菜单
    QMenu *menu = mBar->addMenu("对话框");

    //添加动作
    QAction *p1 = menu->addAction("模态对话框");

    connect(p1,&QAction::triggered,[=](){
        //创建对话框
        QDialog dialog;
        dialog.exec();
        qDebug()<<"111111";
    });

    QAction *p2 = menu->addAction("非模态对话框");

    connect(p2,&QAction::triggered,[=](){
//        dialog.show();
//        qDebug()<<"111111";

//        QDialog *p = new QDialog(this);
//        p->show();

        QDialog *p = new QDialog;
        p->setAttribute(Qt::WA_DeleteOnClose);
        p->show();
    });

    QAction *p3 = menu->addAction("关于对话框");

    connect(p3,&QAction::triggered,[=](){
        //about，关于对话框
        QMessageBox::about(this,"about","关于qt");
    });

    QAction *p4 = menu->addAction("问题对话框");

    connect(p4,&QAction::triggered,[=](){
        //question:问题对话框，确认，取消，返回按下的结果
        int ret = QMessageBox::question(this,"question","Are you ok?",QMessageBox::Ok,QMessageBox::Cancel);

        switch (ret) {//如果是OK
        case QMessageBox::Ok:
            qDebug() << "I am ok.";
            break;
        case QMessageBox::Cancel://如果是取消
            qDebug() << "I am not feel good.";
            break;
        default:
            break;
        }
    });

    QAction *p5 = menu->addAction("文件对话框");

    connect(p5,&QAction::triggered,[=](){
        //用于打开文件，可以指定文件的类型
        QString path = QFileDialog::getOpenFileName(this,"open","../",
                                                    "image (*.png *.xpm *.jpg);;\
                                                    Text files (*.txt);;\
                                                    XML files (*.xml);;\
                                                    source(*.cpp *.h *.c)");
        qDebug() << path;
    });
}

MainWindow::~MainWindow()
{

}
