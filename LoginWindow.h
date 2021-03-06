#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <WorkerWindow.h>
#include <ui_LoginWindow.h>
#include <goble.h>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    void setTheme(QString theme);
   // MainWindow mainwindow;
private slots:
    void on_Blogin_clicked();

    void on_comboBox_theme_activated(int index);

private:
    Ui::LoginWindow *ui;
};

#endif // MAINWINDOW_H
