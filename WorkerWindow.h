#ifndef MAINW_H
#define MAINW_H

#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class WorkerWindow;
}

class WorkerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkerWindow(QWidget *parent = 0);
    ~WorkerWindow();
    QStandardItemModel  *tabModel;  //数据模型
    QStandardItemModel *model;  //选择套餐的模型
    QStandardItemModel *recordModel;  //消费记录模型
    QStandardItemModel *DetailModel; //详细记录模型

    double countPrice();    //计算价格
    void Checkout(QStandardItemModel *mod);       //结账

private slots:
    void on_sign_out_triggered();

    void on_Personal_triggered();

    void on_pushButton_personal_save_clicked();

    void on_My_card_triggered();

    void on_diancan_triggered();

    void on_pushButton_clicked();

    void on_pushButton_decrease_clicked();

    void on_pushButton_2_clicked();

    void on_Dining_record_triggered();

    void on_tableView_diningRecord_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::WorkerWindow *ui;
};

#endif // MAINW_H
