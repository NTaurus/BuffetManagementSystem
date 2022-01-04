#include "LoginWindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}
