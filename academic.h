#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Academic;
}

class Academic : public QDialog
{
    Q_OBJECT

public:
    explicit Academic(int userId,QWidget *parent = nullptr);
    ~Academic();

private slots:
    void on_btnClear_clicked();

    void on_btnSelected_clicked();

    void on_btnSchedule_clicked();

    void on_btnBack_2_clicked();

private:
    Ui::Academic *ui;
    QSqlDatabase db=QSqlDatabase::database();
    int userId;

    void insertData();
    void showData();
    void clearData();
    void clearAll();

};

#endif // ACADEMIC_H
