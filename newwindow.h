#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include "ui_newwindow.h"


namespace Ui {
class NewWindow;
}

class NewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr);
    ~NewWindow();
private slots:
    void on_pushButton_clicked();

    void on_btnBack_clicked();

private:
    Ui::NewWindow *ui;
    QSqlDatabase db=QSqlDatabase::database();
    bool usernameTaken(const QString &username);

};

#endif // NEWWINDOW_H
