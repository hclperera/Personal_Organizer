#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newwindow.h"
#include "dashboard.h"
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
    NewWindow *newWindow;
    Dashboard *dashboard;
    QSqlDatabase db=QSqlDatabase::database();
    int loginOK(const QString &username,const QString &password);
};
#endif // MAINWINDOW_H
