#ifndef PAYFORM_H
#define PAYFORM_H

#include <QWidget>
#include <qstandarditemmodel.h>
namespace Ui {
class PayForm;
}

class PayForm : public QWidget
{
    Q_OBJECT

public:
    explicit PayForm(QWidget *parent = 0);
    ~PayForm();
    QStandardItemModel *mod;
private slots:
    void on_pushButton_clicked();

private:
    Ui::PayForm *ui;
};

#endif // PAYFORM_H
