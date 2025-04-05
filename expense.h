#ifndef EXPENSE_H
#define EXPENSE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Expense;
}

class Expense : public QDialog
{
    Q_OBJECT

public:
    explicit Expense(int userId,QWidget *parent = nullptr);
    ~Expense();

private slots:
    void on_btnBack_2_clicked();

    void on_btnExpense_clicked();

    void on_btnClearALL_clicked();

    void on_btnSelected_clicked();

private:
    Ui::Expense *ui;
    QSqlDatabase db=QSqlDatabase::database();
    int userId;
    void insertData();
    void showData();
    void clearData();
    void clearAll();
    double getExpense(const QString category,int month);
    double getBudget(const QString category,int month);
};

#endif // EXPENSE_H
