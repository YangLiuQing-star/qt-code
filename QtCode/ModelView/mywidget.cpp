#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //打印qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加MYSWQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置主机名
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("test");

    //打开数据库
    if(db.open()==false){//数据库打开失败
        QMessageBox::warning(this,"错误",db.lastError().text());
    }
    qDebug() << "数据库连接成功";

    //设置模型
    model = new QSqlTableModel(this);
    //指定操作的表
    model->setTable("user");

    //把model设置到view中
    ui->tableView->setModel(model);

    //显示model里的数据，查询所有
    model->select();

    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"用户名");
    model->setHeaderData(2,Qt::Horizontal,"密码");

    //设置model的编辑模式，手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置View中的数据库不允许修改
//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MyWidget::~MyWidget()
{
    delete ui;
}

//添加
void MyWidget::on_buttonAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();//获取空记录
    //获取行号
    int row = model->rowCount();
    //插入空记录
    model->insertRecord(row,record);
}


//取消
void MyWidget::on_buttonCancel_clicked()
{
    //取消所有动作
    model->revertAll();
    //提交所有动作
    model->submitAll();
}

//删除
void MyWidget::on_buttonDel_clicked()
{
    //获取选中的模型
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    //取出模型中的索引列表
    QModelIndexList ls = selectModel->selectedRows();

    //删除所有选中的行
    for(int i = 0;i < ls.size();i++){
        model->removeRow(ls.at(i).row());
    }
}

//查询
void MyWidget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString condition = QString("name='%1'").arg(name);
    //过滤条件
    model->setFilter(condition);
    //显示查询的结果
    model->select();
}

void MyWidget::on_buttonCertain_clicked()
{
    //提交操作
    model->submitAll();
}
