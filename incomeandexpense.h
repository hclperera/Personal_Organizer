#ifndef INCOMEANDEXPENSE_H
#define INCOMEANDEXPENSE_H

#include <QDialog>

namespace Ui {
class IncomeAndExpense;
}

class IncomeAndExpense : public QDialog
{
    Q_OBJECT

public:
    explicit IncomeAndExpense(int userId,QWidget *parent = nullptr);
    ~IncomeAndExpense();

private slots:


    void on_btnBack_2_clicked();

    void on_btnIncomeTracker_clicked();

    void on_btnExpenseTracker_clicked();

private:
    Ui::IncomeAndExpense *ui;
    int userId;
};

#endif // INCOMEANDEXPENSE_H
