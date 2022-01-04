#include "payform.h"
#include "ui_payform.h"
#include "WorkerWindow.h"
#include "goble.h"
#include "mysqlcon.h"
#include "qmessagebox.h"
PayForm::PayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PayForm)
{
    ui->setupUi(this);
    char charPrice[20];
    sprintf(charPrice,"%.2f",finalPrice);
    ui->lineEdit_originPrice->setText(charPrice);
    MysqlCon con;
    QSqlQuery result = con.getResult("SELECT COUNT(tb_record.card_Id ) AS numbers FROM  tb_record,tb_consumercard WHERE DATETIME > CURRENT_DATE() AND DATETIME < CURRENT_DATE()+1 AND tb_consumercard.card_Id = tb_record.card_Id AND tb_consumercard.worker_Id = "+user_Id);
    int numbers;
    if(result.next())
        numbers=result.value("numbers").toInt();
    if(numbers<2){
        ui->lineEdit_originPrice_2->setText("本次用餐可享受5折优惠！");
        discount=1;
    }
    else{
        discount=0;
        ui->lineEdit_originPrice_2->setText("今日已用餐两次，无优惠!");
    }
    sprintf(charPrice,"%.2f",discount?finalPrice/2:finalPrice);
    ui->lineEdit_originPrice_3->setText(charPrice);
}

PayForm::~PayForm()
{
    delete ui;
}

void PayForm::on_pushButton_clicked()
{
    double balance, price=discount?finalPrice/2:finalPrice;
    MysqlCon con;
    {
        QSqlQuery result = con.getResult("select balance from tb_consumercard where worker_Id = "+ user_Id);
        if(result.next())
            balance=result.value("balance").toDouble();
        if(balance<price){
            QMessageBox::about(NULL, "提示","余额不足");
            return;
        }
    }
    {
        con.getCon();
        QSqlQuery query(con.ODBC);
        query.prepare("UPDATE tb_consumercard set balance = ? where worker_Id = " + user_Id);
        query.addBindValue(balance-price);
        query.exec();
    }
    WorkerWindow WorkerWindow;
    WorkerWindow.Checkout(mod);
    this->hide();
}
