#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "domxml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //指定初始界面
    on_actionCar_triggered();
    //连接数据库
    connectDB();

    init();

    QStringList ls;
    ls << "二汽神龙" << "毕加索" << "39" << "1" <<"39";
    DomXML::createXML("../demo.xml");
    DomXML::appendXML("../demo.xml",ls);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//车辆管理
void MainWindow::on_actionCar_triggered()
{
    //切换点车辆管理界面
    ui->stackedWidget->setCurrentWidget(ui->car);

    //设置标题
    ui->label->setText("车辆管理");
}

//销售统计
void MainWindow::on_actionCalc_triggered()
{
    //切换到销售统计
    ui->stackedWidget->setCurrentWidget(ui->calc);

    //设置标题
    ui->label->setText("销售统计");
}

//连接数据库
void MainWindow::connectDB(){
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置连接信息
    db.setDatabaseName("car");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");

    //打开数据库
    if(db.open() == false){
        QMessageBox::warning(this,"数据库打开失败",db.lastError().text());
        return;
    }
}

//初始化厂家
void MainWindow::init(){
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);//新建模型
    queryModel->setQuery("select name from factory");//sql语句查询的结果，存储在模型当中

    ui->cbFactory->setModel(queryModel);

    ui->labelLast->setText("0");//剩余数量
    ui->lineEditTotal->setEnabled(false);//金额

    ui->spinBox->setEnabled(false);

    ui->spinBox->setMinimum(0);

    //展示数据库中的所有信息
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(QString("select * from brand"));
    ui->tableView->setModel(model);

}

//厂家下拉框槽函数
void MainWindow::on_cbFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家"){
        //内容清空
        ui->cbBrand->clear();//品牌
        ui->lineEditPrice->clear();//价格
        ui->labelLast->setText("0");//剩余量
        ui->spinBox->setValue(0);//数量选择框
        ui->lineEditTotal->clear();//金额
    }else{
        //查询显示厂家生产的汽车品牌
        QSqlQuery query;
        QString sql = QString("select * from brand where factory='%1'").arg(arg1);

        query.exec(sql);

        //遍历结果集
        while(query.next()){
            QString name = query.value("name").toString();
            //添加内容到品牌下拉框
            ui->cbBrand->addItem(name);//品牌      
        }

    }
}

//品牌下拉框槽函数
void MainWindow::on_cbBrand_currentIndexChanged(const QString &arg1)
{

    QSqlQuery query;

    //根据name，查出其对应的价格，剩余量，数量，余额
    QString findByBrand = QString("select * from brand where name = '%1'").arg(arg1);
    //执行查询
    query.exec(findByBrand);
    while(query.next()){
        QString price = query.value("price").toString();
        QString sum = query.value("sum").toString();
        int sell = query.value("sell").toInt();
        QString last = query.value("last").toString();

        ui->lineEditPrice->setText(price);//价格
        ui->labelLast->setText(sum);//剩余量
        ui->spinBox->setValue(sell);//数量选择框
        ui->lineEditTotal->setText(last);//金额
    }

    //品牌选择完成，开启数量选择框
    ui->spinBox->setEnabled(true);
}

//数量选择框槽函数
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //总量
    int last = 0;
    QSqlQuery query;
    //获取厂家，品牌
    QString factoryStr = ui->cbFactory->currentText();
    QString brandStr = ui->cbBrand->currentText();
    //获取数据库中的总量
    QString sql = QString("select sum,last from brand where factory='%1' and name='%2'")
            .arg(factoryStr)
            .arg(brandStr);
    query.exec(sql);
    while(query.next()){
        last = query.value("last").toInt();
    }

    //剩余量 = last - 选择的数量
    int left = last - arg1;
    if(arg1 > last){//如果选择的数量超过剩余量，终止程序
        //可选择的上限
        ui->spinBox->setValue(last);
        return;
    }
    //更新剩余数量
    ui->labelLast->setText(QString::number(left));
    //金额 = 数量 * 单价
    int total = arg1 * ui->lineEditPrice->text().toInt();
    //更新金额
    ui->lineEditTotal->setText(QString::number(total));
    //点击确认，更新数据库的库存和销量
}

//更新数据库信息，销量和剩余量
void MainWindow::on_btCertain_clicked()
{
    QSqlQuery query;
    //获取当前汽车的厂家和名字
    QString curFactory = ui->cbFactory->currentText();
    QString curBrand = ui->cbBrand->currentText();

    //获取当前销量
    int sellNum = ui->spinBox->value();
    //获取车辆当前的剩余量
    int remaining = ui->labelLast->text().toInt();

    //更新数据库
    QString sql = QString("update brand set sell=%1,last=%2 where factory='%3' and name='%4'")
            .arg(sellNum)
            .arg(remaining)
            .arg(curFactory)
            .arg(curBrand);

    //执行SQL语句
    query.exec(sql);

    ui->btCertain->setEnabled(false);
}

//取消按钮，重新初始化
void MainWindow::on_btCancel_clicked()
{
    on_cbFactory_currentIndexChanged("请选择厂家");
}
