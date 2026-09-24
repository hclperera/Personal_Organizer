#ifndef BUDGET_H
#define BUDGET_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Budget;
}

class Budget : public QDialog
{
    Q_OBJECT

public:
    explicit Budget(int userId,QWidget *parent = nullptr);
    ~Budget();

private slots:
    void on_btnBack_2_clicked();

    void on_btnSelected_clicked();

    void on_btnClearALL_clicked();

    void on_btnBudget_clicked();

private:
    Ui::Budget *ui;
    int userId;
    QSqlDatabase db=QSqlDatabase::database();
    void insertData();
    void showData();

    void clearAll();
    void clearData();

};

#endif // BUDGET_H
