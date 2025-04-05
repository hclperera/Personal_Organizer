#include "newwindow.h"
#include "ui_newwindow.h"
#include "mainwindow.h"
#include <QBoxLayout>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QMessageBox>
#include <QString>



NewWindow::NewWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewWindow)
{
    ui->setupUi(this);


}

NewWindow::~NewWindow()
{
    delete ui;
}
bool NewWindow::usernameTaken(const QString &username){
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()){
        return query.value(0).toInt() > 0;
    }  else {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return false;
    }


}


void NewWindow::on_pushButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();


    if(username.isEmpty()||password.isEmpty()||confirmPassword.isEmpty()){
        QMessageBox::warning(this,"Error","Please Fill in All Fields!!");
        return;

    }
    if(password!=confirmPassword){
        QMessageBox::warning(this,"Error","Passwords do not match !");
        return;
    }
    if(usernameTaken(username)){
        QMessageBox::warning(this, "Error", "This Username is Already Taken. Please Select a Different One.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO users(username,password) VALUES (:username,:password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()){
        qDebug()<<"Error : "<<query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to register user.");
        return;
    }

    QMessageBox::information(this,"Sucess!","User Registration Sucessfull!");
    this->close();

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
    if (mainWindow) {
        mainWindow->show();
    }

}


void NewWindow::on_btnBack_clicked()
{
    this->close();
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
    if (mainWindow) {
        mainWindow->show();
    }
}

