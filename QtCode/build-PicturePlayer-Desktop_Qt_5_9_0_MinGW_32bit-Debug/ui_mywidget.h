/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidget
{
public:
    QWidget *widget;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnCircle;
    QPushButton *btnLarge;
    QPushButton *btnSmaller;

    void setupUi(QWidget *MyWidget)
    {
        if (MyWidget->objectName().isEmpty())
            MyWidget->setObjectName(QStringLiteral("MyWidget"));
        MyWidget->resize(666, 468);
        widget = new QWidget(MyWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 20, 601, 421));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(100, 20, 403, 391));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnStart = new QPushButton(widget1);
        btnStart->setObjectName(QStringLiteral("btnStart"));

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(widget1);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        horizontalLayout->addWidget(btnStop);

        btnCircle = new QPushButton(widget1);
        btnCircle->setObjectName(QStringLiteral("btnCircle"));

        horizontalLayout->addWidget(btnCircle);

        btnLarge = new QPushButton(widget1);
        btnLarge->setObjectName(QStringLiteral("btnLarge"));

        horizontalLayout->addWidget(btnLarge);

        btnSmaller = new QPushButton(widget1);
        btnSmaller->setObjectName(QStringLiteral("btnSmaller"));

        horizontalLayout->addWidget(btnSmaller);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MyWidget);

        QMetaObject::connectSlotsByName(MyWidget);
    } // setupUi

    void retranslateUi(QWidget *MyWidget)
    {
        MyWidget->setWindowTitle(QApplication::translate("MyWidget", "MyWidget", Q_NULLPTR));
        label->setText(QApplication::translate("MyWidget", "image", Q_NULLPTR));
        btnStart->setText(QApplication::translate("MyWidget", "\346\222\255\346\224\276", Q_NULLPTR));
        btnStop->setText(QApplication::translate("MyWidget", "\345\201\234\346\255\242", Q_NULLPTR));
        btnCircle->setText(QApplication::translate("MyWidget", "\346\227\213\350\275\254", Q_NULLPTR));
        btnLarge->setText(QApplication::translate("MyWidget", "\346\224\276\345\244\247", Q_NULLPTR));
        btnSmaller->setText(QApplication::translate("MyWidget", "\347\274\251\345\260\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyWidget: public Ui_MyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
