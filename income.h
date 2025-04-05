#ifndef INCOME_H
#define INCOME_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Income;
}

class Income : public QDialog
{
    Q_OBJECT

public:
    explicit Income(int userId,QWidget *parent = nullptr);
    ~Income();

private slots:
    void on_btnBack_2_clicked();

    void on_btnAdd_clicked();

    void on_btnClear_clicked();

    void on_btnSelected_clicked();

private:
    Ui::Income *ui;
    QSqlDatabase db=QSqlDatabase::database();
    int userId;

    void insertData();
    void showData();
    void clearData();
    void clearAll();
};

#endif // INCOME_H
