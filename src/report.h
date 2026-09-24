#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(int userId,QWidget *parent = nullptr);
    ~Report();

private slots:
    void on_btnBack_2_clicked();

    void on_btnSubmit_clicked();

private:
    Ui::Report *ui;
    int userId;
    QSqlDatabase db=QSqlDatabase::database();
    void displayMonthlyReport();
    void INshowData(QString my);
    void EXshowData(QString my);
};

#endif // REPORT_H
