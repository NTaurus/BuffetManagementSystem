#ifndef MYSQLCON_H
#define MYSQLCON_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
class MysqlCon
{
public:
    QSqlDatabase ODBC;
public:
        QSqlDatabase getCon(){
            //MysqlCon mysql
            this->ODBC = QSqlDatabase::addDatabase("QODBC");
            this->ODBC.setHostName("localhost");
            this->ODBC.setPort(3306);
            this->ODBC.setDatabaseName("buffet");
            this->ODBC.setUserName("root");
            this->ODBC.setPassword("Limit0502");
            this->ODBC.open();
            return this->ODBC;
        }

        QSqlQuery getResult(QString sql){
            QSqlDatabase db;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
                db=QSqlDatabase::database("qt_sql_default_connection");
            else
                db = getCon();
            QSqlQuery result = db.exec(sql);
            return result;
        }

};


#endif // MYSQLCON_H
