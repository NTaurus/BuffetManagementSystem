#include "AdminWindow.h"
#include "ui_adminwindow.h"
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
AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    QDateTime curDateTime=QDateTime::currentDateTime(); //获取当前日期
    ui->dbEdit_end->setDate(curDateTime.date());
    this->setWindowTitle("欢迎您，"+user_Name);
    this->setWindowIcon(QIcon(":/Image/images/管理员.png"));
    ui->stackedWidget->setCurrentIndex(3);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_sign_out_triggered()   //退出登录
{
    int tn = QMessageBox::question(this, "提示", "确定要退出登录吗?", QMessageBox::Yes|QMessageBox::No);
    if (tn == QMessageBox::Yes){
        this->close();
        LoginWindow *loginwindow = new LoginWindow();
        loginwindow->show();
    }
}

void AdminWindow::on_actionDiningRecord_triggered() //就餐记录
{
    ui->stackedWidget->setCurrentIndex(0);

    recordModel=new QStandardItemModel(0,5,ui->tableView_diningRecord);
    ui->tableView_diningRecord->setModel(recordModel);
    ui->tableView_diningRecord->verticalHeader()->setVisible(false);

    recordModel->setHeaderData(0,Qt::Horizontal,tr("工号"));
    recordModel->setHeaderData(1,Qt::Horizontal,tr("单号"));
    recordModel->setHeaderData(2,Qt::Horizontal,tr("时间"));
    recordModel->setHeaderData(3,Qt::Horizontal,tr("总价"));
    recordModel->setHeaderData(4,Qt::Horizontal,tr("实付"));

    ui->tableView_diningRecord->setColumnWidth(0,100);
    ui->tableView_diningRecord->setColumnWidth(1,100);
    ui->tableView_diningRecord->setColumnWidth(2,240);
    ui->tableView_diningRecord->setColumnWidth(3,85);
    ui->tableView_diningRecord->setColumnWidth(4,85);
    ui->tableView_diningRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);

    MysqlCon con;
    con.getCon();
    QSqlQuery resultRecord(con.ODBC);
    {
        ui->comboBox_worker->clear();
        ui->comboBox_worker->addItem("所有人");
        QString sql = "SELECT worker_Id FROM tb_worker";
        resultRecord.prepare(sql);
        resultRecord.exec();
        while(resultRecord.next())
            ui->comboBox_worker->addItem(resultRecord.value("worker_Id").toString());
    }

    {
        QString sql = "SELECT tb_worker.worker_Id, tb_record.record_Id, tb_record.datetime, SUM(tb_menu.price * tb_detail.numbers) AS total_price, tb_record.discount FROM tb_worker, tb_consumercard, tb_record, tb_detail, tb_menu WHERE tb_worker.worker_Id = tb_consumercard.worker_Id  AND tb_consumercard.card_Id = tb_record.card_Id AND tb_record.record_Id = tb_detail.record_Id AND tb_detail.food_Id = tb_menu.food_Id GROUP BY(tb_record.record_Id)";
        resultRecord.prepare(sql);
        resultRecord.exec();
        for(int i=0;resultRecord.next();i++){
            recordModel->setItem(i,0,new QStandardItem(resultRecord.value("worker_Id").toString()));
            recordModel->setItem(i,1,new QStandardItem(resultRecord.value("record_Id").toString()));
            recordModel->setItem(i,2,new QStandardItem(resultRecord.value("datetime").toString()));
            recordModel->setItem(i,3,new QStandardItem(resultRecord.value("total_price").toString()));
            char strPrice[20];
            double price = resultRecord.value("discount").toInt()==1?resultRecord.value("total_price").toDouble()/2:resultRecord.value("total_price").toDouble();
            sprintf(strPrice,"%.2f",price);
            recordModel->setItem(i,4,new QStandardItem(strPrice));
        }
    }
    ui->tableView_diningRecord->setAutoScrollMargin(4);
}

void AdminWindow::on_pushButton_clicked()   //就餐记录的查询动作
{
    int L=recordModel->rowCount(),i=0;
    for(int j=L-1;j>=0;j--) //为保留model的格式不变，不用clear()
        recordModel->removeRow(j);
    {
        MysqlCon con;
        con.getCon();
        QSqlQuery resultRecord(con.ODBC);
        QString sql = "SELECT tb_worker.worker_Id, tb_record.record_Id, tb_record.datetime, SUM(tb_menu.price * tb_detail.numbers) AS total_price, tb_record.discount FROM tb_worker, tb_consumercard, tb_record, tb_detail, tb_menu WHERE tb_worker.worker_Id = tb_consumercard.worker_Id  AND tb_consumercard.card_Id = tb_record.card_Id AND tb_record.record_Id = tb_detail.record_Id AND tb_detail.food_Id = tb_menu.food_Id AND DATETIME >= '" + ui->dbEdit_begin->text()+ "' AND DATETIME <= '" + ui->dbEdit_end->text() + "' ";

        if(ui->comboBox_worker->currentText() != "所有人")
            sql += " AND tb_worker.worker_Id = " + ui->comboBox_worker->currentText();
        sql += " GROUP BY(tb_record.record_Id)";
        resultRecord.prepare(sql);
        resultRecord.exec();
        for(i=0;resultRecord.next();i++){
            recordModel->setItem(i,0,new QStandardItem(resultRecord.value("worker_Id").toString()));
            recordModel->setItem(i,1,new QStandardItem(resultRecord.value("record_Id").toString()));
            recordModel->setItem(i,2,new QStandardItem(resultRecord.value("datetime").toString()));
            recordModel->setItem(i,3,new QStandardItem(resultRecord.value("total_price").toString()));
            char strPrice[20];
            double price = resultRecord.value("discount").toInt()==1?resultRecord.value("total_price").toDouble()/2:resultRecord.value("total_price").toDouble();
            sprintf(strPrice,"%.2f",price);
            recordModel->setItem(i,4,new QStandardItem(strPrice));
        }
        if(i==0)
            QMessageBox::about(NULL, "提示", "无记录！");
    }
}

void AdminWindow::on_tableView_diningRecord_clicked(const QModelIndex &index)   //就餐记录明细
{

    int row=ui->tableView_diningRecord->currentIndex().row();    //选择的行
    DetailModel=new QStandardItemModel(0,4,ui->tableView_DetailRecord);
    ui->tableView_DetailRecord->setModel(DetailModel);
    ui->tableView_DetailRecord->verticalHeader()->setVisible(false);

    DetailModel->setHeaderData(0,Qt::Horizontal,tr("明细单号"));
    DetailModel->setHeaderData(1,Qt::Horizontal,tr("菜名"));
    DetailModel->setHeaderData(2,Qt::Horizontal,tr("数量"));
    DetailModel->setHeaderData(3,Qt::Horizontal,tr("总价"));

    ui->tableView_DetailRecord->setColumnWidth(0,135);
    ui->tableView_DetailRecord->setColumnWidth(1,220);
    ui->tableView_DetailRecord->setColumnWidth(2,140);
    ui->tableView_DetailRecord->setColumnWidth(3,140);
    ui->tableView_DetailRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QModelIndex indexN=recordModel->index(row,1);
    QString record_Id=recordModel->data(indexN).toString();
    {
        MysqlCon con;
        QString sql = "SELECT tb_worker.worker_Name, tb_worker.section, tb_worker.position FROM tb_record, tb_worker, tb_consumercard  WHERE tb_consumercard.worker_Id = tb_worker.worker_Id  AND tb_consumercard.card_Id = tb_record.card_Id  AND  tb_record.record_Id = " + record_Id;
        QSqlQuery resultWorker = con.getResult(sql);
        if(resultWorker.next()){
            ui->lineEdit_workerNameDetail->setText(resultWorker.value("worker_Name").toString());
            ui->lineEdit_sectionDetail->setText(resultWorker.value("section").toString());
            ui->lineEdit_positionDetail->setText(resultWorker.value("position").toString());
        }
    }

    {
        MysqlCon con;
        QString sql = "SELECT tb_detail.detail_Id, tb_menu.food_Name, tb_detail.numbers, tb_menu.price * tb_detail.numbers as price FROM  tb_record, tb_menu, tb_detail WHERE  tb_record.record_Id = tb_detail.record_Id AND tb_detail.food_Id = tb_menu.food_Id AND tb_record.record_Id = " + record_Id;
        QSqlQuery resultDetail = con.getResult(sql);
        for(int i=0;resultDetail.next();i++){
            DetailModel->setItem(i,0,new QStandardItem(resultDetail.value("detail_Id").toString()));
            DetailModel->setItem(i,1,new QStandardItem(resultDetail.value("food_Name").toString()));
            DetailModel->setItem(i,2,new QStandardItem(resultDetail.value("numbers").toString()));
            DetailModel->setItem(i,3,new QStandardItem(resultDetail.value("price").toString()));
        }
    }

}

void AdminWindow::on_actionWorker_triggered()   //职工信息
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit_ID->setEnabled(false);

    workerModel=new QStandardItemModel(0,6,ui->tableView_worker);
    ui->tableView_worker->setModel(workerModel);
    ui->tableView_worker->verticalHeader()->setVisible(false);

    workerModel->setHeaderData(0,Qt::Horizontal,tr("工号"));
    workerModel->setHeaderData(1,Qt::Horizontal,tr("名字"));
    workerModel->setHeaderData(2,Qt::Horizontal,tr("性别"));
    workerModel->setHeaderData(3,Qt::Horizontal,tr("部门"));
    workerModel->setHeaderData(4,Qt::Horizontal,tr("职位"));
    workerModel->setHeaderData(5,Qt::Horizontal,tr("电话"));

    ui->tableView_worker->setColumnWidth(0,95);
    ui->tableView_worker->setColumnWidth(1,95);
    ui->tableView_worker->setColumnWidth(2,95);
    ui->tableView_worker->setColumnWidth(3,100);
    ui->tableView_worker->setColumnWidth(4,100);
    ui->tableView_worker->setColumnWidth(5,145);
    ui->tableView_worker->setEditTriggers(QAbstractItemView::NoEditTriggers);
    {
        MysqlCon con;
        QString sql="select *from tb_worker";
        QSqlQuery result = con.getResult(sql);
        for(int i=0;result.next();i++){
            workerModel->setItem(i,0,new QStandardItem(result.value("worker_Id").toString()));
            workerModel->setItem(i,1,new QStandardItem(result.value("worker_Name").toString()));
            workerModel->setItem(i,2,new QStandardItem(result.value("sex").toString()));
            workerModel->setItem(i,3,new QStandardItem(result.value("section").toString()));
            workerModel->setItem(i,4,new QStandardItem(result.value("position").toString()));
            workerModel->setItem(i,5,new QStandardItem(result.value("phone").toString()));
        }
    }
}



void AdminWindow::on_tableView_worker_clicked(const QModelIndex &index)
{
    int row=ui->tableView_worker->currentIndex().row();    //选择的行

    QModelIndex indexN=workerModel->index(row,0);   //工号
    ui->lineEdit_ID->setText(workerModel->data(indexN).toString());

    indexN=workerModel->index(row,1);               //名字
    ui->lineEdit_Name->setText(workerModel->data(indexN).toString());

    indexN=workerModel->index(row,2);               //性别
    ui->comboBox_sex->setCurrentText(workerModel->data(indexN).toString());

    indexN=workerModel->index(row,3);               //部门
    ui->comboBox_section->setCurrentText(workerModel->data(indexN).toString());

    indexN=workerModel->index(row,4);               //职位
    ui->lineEdit_Position->setText(workerModel->data(indexN).toString());

    indexN=workerModel->index(row,5);               //电话
    ui->lineEdit_Phone->setText(workerModel->data(indexN).toString());

}

void AdminWindow::on_pushButton_workerSave_clicked()
{

    MysqlCon con;
    con.getCon();
    QSqlQuery query(con.ODBC);
    QString sql = "UPDATE tb_worker SET worker_Name = '" + ui->lineEdit_Name->text() +"', sex = '" +ui->comboBox_sex->currentText()+"', section = '" + ui->comboBox_section->currentText()+"', position = '" + ui->lineEdit_Position->text() + "', phone = '" + ui->lineEdit_Phone->text() +"' WHERE worker_Id = "+ui->lineEdit_ID->text();
    if(query.exec(sql))
        QMessageBox::about(NULL, "提示", "更新成功！");
    else
        QMessageBox::about(NULL, "提示", "更新失败！");

}

void AdminWindow::on_pushButton_init_clicked()
{
    ui->lineEdit_ID->setEnabled(true);
    ui->lineEdit_ID->setText("");
    ui->lineEdit_Name->setText("");
    ui->lineEdit_Phone->setText("");
    ui->lineEdit_Position->setText("");
}


void AdminWindow::on_pushButton_insert_clicked()
{
    MysqlCon con;
    con.getCon();
    QSqlQuery query(con.ODBC);
    QString sql = "INSERT into tb_worker(worker_Id, worker_Name, sex, section, position, phone) values(" + ui->lineEdit_ID->text() + ", '" + ui->lineEdit_Name->text() +"' , '" +ui->comboBox_sex->currentText() + "' , '" + ui->comboBox_section->currentText() + "' , '" + ui->lineEdit_Position->text() +"' , '" + ui->lineEdit_Phone->text() + "')";
    if(query.exec(sql))
        QMessageBox::about(NULL, "提示", "添加成功!");
    else
        QMessageBox::about(NULL, "提示", "添加失败！");
    AdminWindow::on_actionWorker_triggered();   //更新表
}

void AdminWindow::on_pushButton_queryInit_clicked()
{
    AdminWindow::on_pushButton_init_clicked();
}


void AdminWindow::on_pushButton_queryResult_clicked()
{
    ui->lineEdit_ID->setEnabled(false);
    int L = workerModel->rowCount();
    for(int i=L-1;i>=0;i--)
        workerModel->removeRow(i);
    MysqlCon con;
    QString sql="select *from tb_worker WHERE ";
    if(ui->lineEdit_ID->text()!="")
        sql += ("worker_Id = "+ui->lineEdit_ID->text()) + " and ";
    if(ui->lineEdit_Name->text()!="")
        sql += ("worker_Name = '" + ui->lineEdit_Name->text()) + "' and ";
    if(ui->comboBox_section->currentText()!="")
        sql += "section = '" + ui->comboBox_section->currentText() + "' and ";
    if(ui->lineEdit_Position->text()!="")
        sql += "position = '%" + ui->lineEdit_Position->text() + "%' and ";
    if(ui->lineEdit_Phone->text()!="")
        sql += "phone = '" + ui->lineEdit_Phone->text() + "' and ";
    sql += "sex like '%" + ui->comboBox_sex->currentText() + "%'";
    //QMessageBox::about(NULL, "提示", sql);

    QSqlQuery result = con.getResult(sql);
    for(int i=0;result.next();i++){
        workerModel->setItem(i,0,new QStandardItem(result.value("worker_Id").toString()));
        workerModel->setItem(i,1,new QStandardItem(result.value("worker_Name").toString()));
        workerModel->setItem(i,2,new QStandardItem(result.value("sex").toString()));
        workerModel->setItem(i,3,new QStandardItem(result.value("section").toString()));
        workerModel->setItem(i,4,new QStandardItem(result.value("position").toString()));
        workerModel->setItem(i,5,new QStandardItem(result.value("phone").toString()));
    }
    if(!result.size())
        QMessageBox::about(NULL, "提示", "无记录！");

}

void AdminWindow::on_Cost_statistics_triggered()
{
    
}

void AdminWindow::on_pushButton_refresh_clicked()//刷新
{
    AdminWindow::on_actionWorker_triggered();
}

void AdminWindow::actionCost_information(QString st,QString ed){


    costModel=new QStandardItemModel(0,5,ui->tableView_costRecord);
    ui->tableView_costRecord->setModel(costModel);
    ui->tableView_costRecord->verticalHeader()->setVisible(false);

    costModel->setHeaderData(0,Qt::Horizontal,tr("单号"));
    costModel->setHeaderData(1,Qt::Horizontal,tr("名字"));
    costModel->setHeaderData(2,Qt::Horizontal,tr("时间"));
    costModel->setHeaderData(3,Qt::Horizontal,tr("总价"));
    costModel->setHeaderData(4,Qt::Horizontal,tr("公司补贴"));
    //costModel->setHeaderData(5,Qt::Horizontal,tr("电话"));

    ui->tableView_costRecord->setColumnWidth(0,95);
    ui->tableView_costRecord->setColumnWidth(1,95);
    ui->tableView_costRecord->setColumnWidth(2,230);
    ui->tableView_costRecord->setColumnWidth(3,95);
    ui->tableView_costRecord->setColumnWidth(4,95);
    ui->tableView_costRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);


    MysqlCon con;
    QString sql="SELECT tb_worker.worker_Id,tb_worker.worker_Name,tb_record.record_Id, tb_record.datetime, SUM(tb_menu.price) AS priceSum FROM tb_worker,tb_consumercard,tb_detail,tb_record,tb_menu WHERE tb_worker.worker_Id=tb_consumercard.worker_Id  AND tb_consumercard.card_Id=tb_record.card_Id AND tb_record.discount=1 AND tb_detail.record_Id = tb_record.record_Id AND tb_detail.food_Id = tb_menu.food_Id GROUP BY tb_record.record_Id";
    QSqlQuery result=con.getResult(sql);

    int i=0;
    double sum=0.0;
    while(result.next()){
        QString t=result.value("datetime").toString();
        if(t>=st&&t<=ed){
            costModel->setItem(i,0,new QStandardItem(result.value("record_Id").toString()));
            costModel->setItem(i,1,new QStandardItem(result.value("worker_Name").toString()));
            costModel->setItem(i,2,new QStandardItem(result.value("datetime").toString()));
            costModel->setItem(i,3,new QStandardItem(result.value("priceSum").toString()));

            double price=result.value("priceSum").toDouble()/2;
            char priceStr[10];
            sprintf(priceStr,"%.2f",price);
            costModel->setItem(i++,4,new QStandardItem(priceStr));

            sum+=price;
        }
    }
    char sumStr[10],cost_count[10];
    sprintf(sumStr,"%.2f",sum);
    sprintf(cost_count,"%d",i+1);
    ui->label_price->setText(sumStr);
    ui->label_cost_count->setText(cost_count);
}

void AdminWindow::on_actionCost_information_triggered() //支出记录
{
    ui->stackedWidget->setCurrentIndex(2);

    QDateTime curDateTime=QDateTime::currentDateTime();
    QString nextDay=curDateTime.addDays(1).toString("yyyy-MM-dd");

    actionCost_information(ui->dbEdit_begin_cost->text(),nextDay);
}

void AdminWindow::on_pushButton_cost_record_query_clicked()
{
    actionCost_information(ui->dbEdit_begin_cost->text(),ui->dbEdit_end_cost->text());
}


void AdminWindow::on_pushButton_cost_record_month_clicked()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString nextDay=curDateTime.addDays(1).toString("yyyy-MM-dd");
    QString st=curDateTime.addMonths(-1).toString("yyyy-MM-dd");
    actionCost_information(st,nextDay);
}

void AdminWindow::on_pushButton_cost_record_Quarterly_clicked()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString nextDay=curDateTime.addDays(1).toString("yyyy-MM-dd");
    QString st=curDateTime.addMonths(-3).toString("yyyy-MM-dd");
    actionCost_information(st,nextDay);
}

void AdminWindow::on_pushButton_cost_record_year_clicked()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString nextDay=curDateTime.addDays(1).toString("yyyy-MM-dd");
    QString st=curDateTime.addYears(-1).toString("yyyy-MM-dd");
    actionCost_information(st,nextDay);
}
