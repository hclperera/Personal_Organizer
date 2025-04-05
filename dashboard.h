#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QSqlDatabase>
#include <QCloseEvent>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(int userId,QWidget *parent = nullptr);
    ~Dashboard();

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_btnLogout_clicked();

    void on_btnIncomeAndExpense_clicked();

    void on_btnSetBudget_clicked();

    void on_btnAcademic_clicked();

    void on_btnFinancial_clicked();

private:
    Ui::Dashboard *ui;
    int userId;
    void checkUpcoming();

    QSqlDatabase db=QSqlDatabase::database();

};

#endif // DASHBOARD_H
