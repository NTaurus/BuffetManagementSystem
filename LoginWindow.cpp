#include <LoginWindow.h>
#include "ui_loginwindow.h"
#include "QMessageBox"
#include <iostream>
#include <mysqlcon.h>
#include <QtSql/QSqlDatabase>
#include "QtSql/QSqlQuery"
#include <WorkerWindow.h>
#include <goble.h>
#include <AdminWindow.h>
#include <QFile>
#include <Qicon>
using namespace std;
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
//    ui->lineEdit->setText("9003");
//    ui->lineEdit_2->setText("123");
    this->setWindowTitle("欢迎登录");
    setTheme(theme[2]);  //默认主题
    this->setWindowIcon(QIcon(":/Image/images/登录-用户.png"));

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Blogin_clicked()
{

    MysqlCon con;
    QString sql="";
    if(ui->comboBox->currentIndex()==0)
        sql="select * from tb_worker,tb_consumercard where tb_worker.worker_Id= "+ ui->lineEdit->text()+" and tb_worker.worker_Id = tb_consumercard.worker_Id";
    else
        sql="select *from tb_admin where admin_Id = "+ui->lineEdit->text()+";";
    //QMessageBox::about(NULL, "提示", ui->lineEdit->text());
    QSqlQuery result = con.getResult(sql);
    QString user=ui->lineEdit->text(),password;
    if(result.next()){
        password = result.value("password").toString();
        //QMessageBox::about(NULL, "提示", result.value("worker_Name").toString());
        user_Id=ui->lineEdit->text();
        userCard_Id=result.value("card_Id").toString();
        user_Name=result.value("worker_Name").toString();
        if(user_Name=="")
            user_Name=result.value("admin_Name").toString();
    }
    if(user==""){
        QMessageBox::about(NULL, "提示", "用户名不能为空！");
    }
    else{
        if(ui->lineEdit_2->text()==""){
           QMessageBox::about(NULL, "提示", "密码不能为空！");
        }
        else{
            if(password == ui->lineEdit_2->text()){
                if(ui->comboBox->currentIndex()==0){
                    QMessageBox::about(NULL,"提示", "登录成功！");
                    WorkerWindow *workerwindow = new WorkerWindow;
                    this->hide();
                    workerwindow->show();
                }
//                else if(result.value("position").toString()=="经理"){
                else {
                    QMessageBox::about(NULL,"提示", "登录成功！");
                    AdminWindow *admin = new AdminWindow;
                    this->hide();
                    admin->show();
                }
//                else QMessageBox::about(NULL,"提示", "登录失败，您不是管理员！");
                con.ODBC.close();
            }
            else{
                QMessageBox::about(NULL, "提示","账号或密码错误！");
                ui->lineEdit_2->setText("");
            }
        }
    }
    con.ODBC.close();
}

void LoginWindow::setTheme(QString theme){  //设置树题函数
    QFile file(theme);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
}

void LoginWindow::on_comboBox_theme_activated(int index)    //设置主题按钮
{
    setTheme(theme[index]);
}
