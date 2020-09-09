#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //打印qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加MYSWQL数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置主机名，用户名，密码，数据库名
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("test");

    //打开数据库
    if(db.open()==false){//数据库打开失败
        QMessageBox::warning(this,"错误",db.lastError().text());
    }
    qDebug() << "数据库连接成功";

    QSqlQuery query;
    query.exec("select * from user");
    //遍历
    while(query.next()){
        //取出当前行的内容，转化成相应的类型
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString()
                 << query.value("password").toString();
    }

//    query.exec("CREATE TABLE qt ( `id` int NOT NULL,`name` varchar(255) NOT NULL,PRIMARY KEY (`id`))");

//    //插入
//    query.exec("insert");
//    //批量插入，odbc风格
//    //预处理语句
//    query.prepare("insert into user (username,password) values(?,?)");
//    //给占位符设置内容，List
//    QVariantList nameList;
//    nameList << "小米" << "123";
//    QVariantList passwordList;
//    passwordList << "11" << "22";

//    //给字段绑定相应的值，按顺序进行绑定
//    query.addBindValue(nameList);
//    query.addBindValue(passwordList);

//    //执行预处理命令
//    query.execBatch();

//    //oracle风格
//    //占位符:
//    query.prepare("insert into user (username,password) values(:username,:password)");

//    //给占位符设置内容，List
//    QVariantList nameList;
//    nameList << "小米" << "123";
//    QVariantList passwordList;
//    passwordList << "11" << "22";

//    //给字段绑定相应的值，按顺序进行绑定
//    query.bindValue(":name",nameList);
//    query.bindValue(":password",passwordList);

//    //执行预处理命令
//    query.execBatch();

}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_buttonDel_clicked()
{
    //获取行编辑的内容
    int id = ui->lineEdit->text().toInt();

    QString sql = QString("delete from user where id = %1").arg(id);

    //开启一个事务
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.exec(sql);
}

//确定删除
void MyWidget::on_buttonSure_clicked()
{
    //提交事务
    QSqlDatabase::database().commit();

}

void MyWidget::on_buttonCancel_clicked()
{
    QSqlDatabase::database().rollback();
}
