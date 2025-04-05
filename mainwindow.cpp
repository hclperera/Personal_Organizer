#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newwindow.h"
#include "dashboard.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , newWindow(nullptr),dashboard(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete newWindow;
    delete dashboard;
}



void MainWindow::on_btnRegister_clicked()
{
    this->hide();
    if (!newWindow) {
        newWindow = new NewWindow(this);
    }
    newWindow->show();
}


int MainWindow::loginOK(const QString &username,const QString &password)
{

    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int userId = query.value(0).toInt();
        return userId;
    } else {
        qDebug() << "Error: "<<query.lastError().text();
        return -1;
    }
}


void MainWindow::on_btnLogin_clicked()
{
    QString username = ui->LineUsername->text();
    QString password = ui->LinePassword->text();

    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this,"Error","Please Fill in All Fields!!");
        return;
    }
    int userId=loginOK(username,password);

    if(userId != -1){
        QMessageBox::information(this, "Sucess", "Login Sucessful");
        qDebug() << "Attempting login with Username:" << username << " Password:" << password<<"UserID : "<<userId;

        this->close();

        dashboard = new Dashboard(userId,this);
        dashboard->show();

    }

    else{
        QMessageBox::warning(this, "Error", "Incorrect username or password.");
    }
}

