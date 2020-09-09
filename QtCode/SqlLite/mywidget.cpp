#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //打印qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    qDebug() << "数据库驱动加载成功";

    //添加MYSWQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //设置数据库
    db.setDatabaseName("../info.db");

    if(!db.open()){
        QMessageBox::warning(this,"错误信息",db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("create table user(id int primary key, username varchar(255),password varchar(255) )");

    qDebug() << "数据库表创建成功";

    //预处理语句
    query.prepare("insert into user(id,username,password) values(?,?,?)");
    //给占位符设置内容，List
    QVariantList idList;
    idList << 1 << 2 << 3 << 4 << 5;
    QVariantList nameList;
    nameList << "小米" << "红米" << "华为" << "opp" << "vivo";
    QVariantList passwordList;
    passwordList << "11" << "22" << "33" << "44" << "5";

    //给字段绑定相应的值，按顺序进行绑定
    query.addBindValue(idList);
    query.addBindValue(nameList);
    query.addBindValue(passwordList);

    //执行预处理命令
    query.execBatch();

    query.exec("select * from user");
    while (query.next()) {//遍历结果集
        qDebug() << query.value("id").toInt()
                 << query.value("username").toString()
                 << query.value("password").toString();
    }

}

MyWidget::~MyWidget()
{
    delete ui;
}
