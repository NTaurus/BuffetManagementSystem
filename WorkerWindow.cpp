#include "WorkerWindow.h"
#include "ui_WorkerWindow.h"
#include "LoginWindow.h"
#include "QMessageBox"
#include "QtSql/QSqlDatabase"
#include "LoginWindow.h"
#include "mysqlcon.h"
#include "goble.h"
#include "QStandardItemModel"
#include "QTableWidgetItem"
#include "QModelIndexList"
#include "string"
#include "payform.h"
using namespace std;
WorkerWindow::WorkerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorkerWindow)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(4);
    this->setWindowTitle("欢迎您，"+user_Name);
    this->setWindowIcon(QIcon(":/Image/images/用户.png"));

}

WorkerWindow::~WorkerWindow()
{
    delete ui;
}

void WorkerWindow::on_sign_out_triggered()
{
    int tn = QMessageBox::question(this, "提示", "确定要退出登录吗?", QMessageBox::Yes|QMessageBox::No);
    if (tn == QMessageBox::Yes){
        this->close();
        LoginWindow *loginwindow = new LoginWindow();
        loginwindow->show();
    }
}

void WorkerWindow::on_Personal_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);

    MysqlCon con;
    QString sql="select *from tb_worker where worker_Id="+user_Id;
    QSqlQuery result = con.getResult(sql);
    if(result.next()){
        ui->lineEdit_ID->setText(result.value("worker_Id").toString());
        ui->lineEdit_Name->setText(result.value("worker_Name").toString());
        ui->comboBox_sex->setCurrentIndex(result.value("sex").toString()=="男"?0:1);
        ui->lineEdit_Section->setText(result.value("section").toString());
        ui->lineEdit_Position->setText(result.value("position").toString());
        ui->lineEdit_Phone->setText(result.value("phone").toString());
    }

}

void WorkerWindow::on_pushButton_personal_save_clicked()
{

    MysqlCon con;
    QString sql = "update tb_worker set phone = " + ui->lineEdit_Phone->text() + " where worker_Id ="+ user_Id;
    QSqlQuery result =con.getResult(sql);
    if(result.isActive())
        QMessageBox::about(NULL, "提示","更新成功！");
    else
        QMessageBox::about(NULL, "提示","更新失败！");
}

void WorkerWindow::on_My_card_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    MysqlCon con;
    QString sql="select *from tb_worker,tb_consumercard where tb_worker.worker_Id = "+user_Id+" and tb_worker.worker_Id = tb_consumercard.worker_Id";
    QSqlQuery result = con.getResult(sql);
    if(result.next()){
        ui->lineEdit_ID_2->setText(result.value("card_Id").toString());
        ui->lineEdit_CardUserName->setText(result.value("worker_Name").toString());
        ui->lineEdit_Balance->setText(result.value("balance").toString());
        ui->lineEdit_RegisterTime->setText(result.value("registerTime").toString());
    }
}

void WorkerWindow::on_diancan_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);

    tabModel=new QStandardItemModel(0,4,ui->tableView);
    ui->tableView->setModel(tabModel);
    ui->tableView->verticalHeader()->setVisible(false);

    tabModel->setHeaderData(0,Qt::Horizontal,tr("菜系号"));
    tabModel->setHeaderData(1,Qt::Horizontal,tr("菜名"));
    tabModel->setHeaderData(2,Qt::Horizontal,tr("价格"));
    tabModel->setHeaderData(3,Qt::Horizontal,tr("图例"));
    
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,200);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MysqlCon con;
    QString sql="select *from tb_menu";
    QSqlQuery result = con.getResult(sql);
    for(int i=0;result.next();i++){
        tabModel->setItem(i,0,new QStandardItem(result.value("food_Id").toString()));
        tabModel->setItem(i,1,new QStandardItem(result.value("food_Name").toString()));
        tabModel->setItem(i,2,new QStandardItem(result.value("price").toString()));
        QString path=":/Image/images/food";
        path.append('1'+i);
        path += ".jpg";
        tabModel->setItem(i,3,new QStandardItem(QIcon(path)," "));
    }

    //选择套餐的表格
    model=new QStandardItemModel(0,4,ui->tableView_2);
    ui->tableView_2->setModel(model);
    ui->tableView_2->verticalHeader()->setVisible(false);

    model->setHeaderData(0,Qt::Horizontal,tr("菜系号"));
    model->setHeaderData(1,Qt::Horizontal,tr("菜名"));
    model->setHeaderData(2,Qt::Horizontal,tr("单价"));
    model->setHeaderData(3,Qt::Horizontal,tr("数量"));

    ui->tableView_2->setColumnWidth(0,120);
    ui->tableView_2->setColumnWidth(1,200);
    ui->tableView_2->setColumnWidth(2,120);
    ui->tableView_2->setColumnWidth(3,200);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setAutoScrollMargin(4);
    ui->tableView_2->setAutoScrollMargin(4);
}

double WorkerWindow::countPrice(){
    //计算价格
    double countPrice=0.0;
    char charPrice[20];
    for(int i=0;i<model->rowCount();i++){
        QModelIndex priceIndex = model->index(i,2);
        QModelIndex numbers = model->index(i,3);
        countPrice+=(model->data(priceIndex).toDouble()*model->data(numbers).toInt());
    }
    sprintf(charPrice,"%.2f",countPrice);
    finalPrice = countPrice;
    ui->lineEdit_price->setText(charPrice);

}

void WorkerWindow::on_pushButton_clicked()
{
    int row=ui->tableView->currentIndex().row();    //选择的行
    if(row==-1){
        QMessageBox::about(NULL, "提示", "请选择套餐！");
        return;
    }
    int isexit=0;
    for(int i=0;i<model->rowCount();i++){   //判断是否已添加该套餐
        QModelIndex index=tabModel->index(row,0);
        QModelIndex index2=model->index(i,0);
        if(index.data().toString()==index2.data().toString()){ //如果已有该套餐，增加数量即可
            isexit=1;
            QModelIndex indexN=model->index(i,3);
            int n=model->data(indexN).toInt()+1;
            char value[20];
            sprintf(value,"%d",n);
            model->setItem(i,3,new QStandardItem(value));
            break;
        }
    }
    if(!isexit){    //如果套餐还没有添加过，添加套餐的全部信息
        int r=model->rowCount();
        for(int i=0;i<3;i++){
            QModelIndex index = tabModel->index(row,i);
            QString val=tabModel->data(index).toString();
            model->setItem(r,i,new QStandardItem(val));
        }
        model->setItem(r,3,new QStandardItem("1"));
    }
    WorkerWindow::countPrice();
}

void WorkerWindow::on_pushButton_decrease_clicked()    //清除购物栏的套餐
{
    int row=ui->tableView_2->currentIndex().row();    //选择的行
    if(row==-1){
        QMessageBox::about(NULL, "提示", "请选择套餐！");
        return;
    }
    QModelIndex indexN=model->index(row,3);
    int numbers=model->data(indexN).toInt();
    if(numbers>1){
        char value[20];
        sprintf(value,"%d",--numbers);
        model->setItem(row,3,new QStandardItem(value));
    }
    else model->removeRow(row);
    WorkerWindow::countPrice();
}

void WorkerWindow::on_pushButton_2_clicked()
{
    if(model->rowCount()==0){
        QMessageBox::about(NULL, "提示", "请选择套餐！");
        return;
    }
    PayForm *payfrom = new PayForm;
    payfrom->mod=model;
    payfrom->show();
}

void WorkerWindow::Checkout(QStandardItemModel *mod){  //需要把model传过来
    MysqlCon con;
    con.getCon();
    {
        QSqlQuery execRecord(con.ODBC);
        execRecord.prepare("insert into tb_record(card_Id,discount) values(?,?)");
        execRecord.addBindValue(userCard_Id);
        execRecord.addBindValue(discount?"1":"0");
        !execRecord.exec();
    }
    QString record_Id="";  //订单记录Id
    {
        QSqlQuery queryRecord(con.ODBC);
        QString sql="SELECT record_Id FROM tb_record WHERE card_Id = " +userCard_Id + " AND DATETIME >= (SELECT MAX(DATETIME) FROM tb_record WHERE card_Id = " + userCard_Id + ")";
        queryRecord.exec(sql);
        if(queryRecord.next())
            record_Id = queryRecord.value("record_Id").toString();
    }
    {
        QSqlQuery queryDetail(con.ODBC);
        for(int i=0;i<mod->rowCount();i++){ //更新Detail表
            QModelIndex indexFood = mod->index(i,0);
            QModelIndex indexNumbers = mod->index(i,3);
            queryDetail.prepare("insert into tb_detail(record_Id,food_Id,numbers) values(?,?,?)");
            queryDetail.addBindValue(record_Id);
            queryDetail.addBindValue(mod->data(indexFood).toString());
            queryDetail.addBindValue(mod->data(indexNumbers).toString());
            queryDetail.exec();
        }
    }
    QMessageBox::about(NULL, "提示", "付款成功！");
}

void WorkerWindow::on_Dining_record_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);

    recordModel=new QStandardItemModel(0,4,ui->tableView_diningRecord);

    ui->tableView_diningRecord->setModel(recordModel);
    ui->tableView_diningRecord->verticalHeader()->setVisible(false);

    recordModel->setHeaderData(0,Qt::Horizontal,tr("单号"));
    recordModel->setHeaderData(1,Qt::Horizontal,tr("时间"));
    recordModel->setHeaderData(2,Qt::Horizontal,tr("总价"));
    recordModel->setHeaderData(3,Qt::Horizontal,tr("实付"));

    ui->tableView_diningRecord->setColumnWidth(0,100);
    ui->tableView_diningRecord->setColumnWidth(1,240);
    ui->tableView_diningRecord->setColumnWidth(2,100);
    ui->tableView_diningRecord->setColumnWidth(3,120);
    ui->tableView_diningRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);

    MysqlCon con;
    con.getCon();
    QString sql = "SELECT tb_record.record_Id, tb_record.datetime, SUM(tb_menu.price * tb_detail.numbers) AS total_price, tb_record.discount FROM tb_record, tb_detail, tb_menu WHERE tb_record.record_Id = tb_detail.record_Id AND tb_detail.food_Id = tb_menu.food_Id AND (tb_record.card_Id = ?) GROUP BY(tb_record.record_Id)";
    QSqlQuery resultRecord(con.ODBC);
    resultRecord.prepare(sql);
    resultRecord.addBindValue(userCard_Id);
    resultRecord.exec();
    for(int i=0;resultRecord.next();i++){
        recordModel->setItem(i,0,new QStandardItem(resultRecord.value("record_Id").toString()));
        recordModel->setItem(i,1,new QStandardItem(resultRecord.value("datetime").toString()));
        recordModel->setItem(i,2,new QStandardItem(resultRecord.value("total_price").toString()));
        char strPrice[20];
        double price = resultRecord.value("discount").toInt()==1?resultRecord.value("total_price").toDouble()/2:resultRecord.value("total_price").toDouble();
        sprintf(strPrice,"%.2f",price);
        recordModel->setItem(i,3,new QStandardItem(strPrice));
    }
}
void WorkerWindow::on_tableView_diningRecord_clicked(const QModelIndex &index)
{
    int row=ui->tableView_diningRecord->currentIndex().row();    //选择的行
    DetailModel=new QStandardItemModel(0,4,ui->tableView_DetailRecord);
    ui->tableView_DetailRecord->setModel(DetailModel);
    ui->tableView_DetailRecord->verticalHeader()->setVisible(false);

    DetailModel->setHeaderData(0,Qt::Horizontal,tr("明细单号"));
    DetailModel->setHeaderData(1,Qt::Horizontal,tr("菜名"));
    DetailModel->setHeaderData(2,Qt::Horizontal,tr("数量"));
    DetailModel->setHeaderData(3,Qt::Horizontal,tr("总价"));

    ui->tableView_DetailRecord->setColumnWidth(0,120);
    ui->tableView_DetailRecord->setColumnWidth(1,200);
    ui->tableView_DetailRecord->setColumnWidth(2,120);
    ui->tableView_DetailRecord->setColumnWidth(3,120);
    ui->tableView_DetailRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QModelIndex indexN=recordModel->index(row,0);
    QString record_Id=recordModel->data(indexN).toString();
    {
        MysqlCon con;
        QString sql = "SELECT tb_detail.detail_Id, tb_menu.food_Name, tb_detail.numbers, tb_menu.price * tb_detail.numbers as price FROM tb_record, tb_menu, tb_detail where tb_record.record_Id = tb_detail.record_Id and tb_detail.food_Id = tb_menu.food_Id and tb_record.card_Id = " + userCard_Id + " and tb_record.record_Id = " + record_Id;
        QSqlQuery resultDetail = con.getResult(sql);
        for(int i=0;resultDetail.next();i++){
            DetailModel->setItem(i,0,new QStandardItem(resultDetail.value("detail_Id").toString()));
            DetailModel->setItem(i,1,new QStandardItem(resultDetail.value("food_Name").toString()));
            DetailModel->setItem(i,2,new QStandardItem(resultDetail.value("numbers").toString()));
            DetailModel->setItem(i,3,new QStandardItem(resultDetail.value("price").toString()));
        }
    }
}


void WorkerWindow::on_pushButton_3_clicked()
{
    int L=recordModel->rowCount(),i=0;
    for(int i=L-1;i>=0;i--) //为保留model的格式不变，不用clear()
        recordModel->removeRow(i);
    {
        MysqlCon con;
        QString sql = "SELECT tb_record.record_Id, tb_record.datetime, SUM(tb_menu.price * tb_detail.numbers) AS total_price, tb_record.discount FROM tb_record, tb_detail, tb_menu WHERE tb_record.record_Id = tb_detail.record_Id AND tb_detail.food_Id = tb_menu.food_Id AND (tb_record.card_Id = + " + userCard_Id + ") AND datetime >= '" + ui->dateEdit->text() + "' AND datetime <= '" + ui->dateEdit_2->text() + "' GROUP BY(tb_record.record_Id)";
        QSqlQuery resultRecord = con.getResult(sql);
        for(;resultRecord.next();i++){
            recordModel->setItem(i,0,new QStandardItem(resultRecord.value("record_Id").toString()));
            recordModel->setItem(i,1,new QStandardItem(resultRecord.value("datetime").toString()));
            recordModel->setItem(i,2,new QStandardItem(resultRecord.value("total_price").toString()));
            char strPrice[20];
            double price = resultRecord.value("discount").toInt()==1?resultRecord.value("total_price").toDouble()/2:resultRecord.value("total_price").toDouble();
            sprintf(strPrice,"%.2f",price);
            recordModel->setItem(i,3,new QStandardItem(strPrice));
        }
        if(i==0)
            QMessageBox::about(NULL, "提示", "无记录！");
    }
}

void WorkerWindow::on_pushButton_4_clicked()
{
    MysqlCon con;
    con.getCon();
    QSqlQuery query(con.ODBC);
    query.prepare("update tb_worker set worker_Name='?', sex = '?', phone='?'  where worker_Id = ?");
    query.addBindValue(ui->lineEdit_Name->text());
    query.addBindValue(ui->comboBox_sex->currentText());
    query.addBindValue(ui->lineEdit_Phone->text());
    query.addBindValue(user_Id);
    query.exec();
    WorkerWindow::on_Personal_triggered();
}
//QMessageBox::about(NULL, "提示", "无记录！");

