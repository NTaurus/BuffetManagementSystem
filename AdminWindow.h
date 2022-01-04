#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();
    QStandardItemModel *recordModel;  //消费记录模型
    QStandardItemModel *DetailModel;  //消费明细模型
    QStandardItemModel *workerModel; //职工模型
    QStandardItemModel *costModel; //支出模型


private slots:
    void on_pushButton_clicked();

    void on_tableView_diningRecord_clicked(const QModelIndex &index);

    void on_sign_out_triggered();

    void on_actionWorker_triggered();

    void on_actionDiningRecord_triggered();

    void on_tableView_worker_clicked(const QModelIndex &index);

    void on_pushButton_workerSave_clicked();

    void on_pushButton_init_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_queryInit_clicked();

    void on_pushButton_queryResult_clicked();

    void on_pushButton_refresh_clicked();

    void on_Cost_statistics_triggered();
    
    void on_actionCost_information_triggered();

    void actionCost_information(QString st,QString ed);

    void on_pushButton_cost_record_query_clicked();

    void on_pushButton_cost_record_month_clicked();

    void on_pushButton_cost_record_Quarterly_clicked();

    void on_pushButton_cost_record_year_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
