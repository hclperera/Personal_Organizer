#include "dashboard.h"
#include "ui_dashboard.h"
#include "mainwindow.h"
#include "incomeandexpense.h"
#include "budget.h"
#include "academic.h"
#include "report.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QApplication>

Dashboard::Dashboard(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
    ,userId(userId)
{
    ui->setupUi(this);
    ui->userIDLabel->setText("Welcome Your UserID is "+ QString::number(userId));

    QTimer *reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &Dashboard::checkUpcoming);
    reminderTimer->start(60000);
}

Dashboard::~Dashboard()
{
    delete ui;
}
void Dashboard::closeEvent(QCloseEvent *event)
{
    QApplication::quit();
    event->accept();
}
void Dashboard::checkUpcoming(){
    QSqlQuery query(db);
    query.prepare("SELECT subject,date,time FROM academic WHERE uid=:id AND type='Assignment'");
    query.bindValue(":id",userId);

    if(!query.exec()){
        qDebug() <<"Select Assignment Error : "<<query.lastError().text();
        return;
    }

    while(query.next()){
        QString subject=query.value(0).toString();
        QString date=query.value(1).toString();
        QString time=query.value(2).toString();

        QString datetimeString = date + " "+ time;
        QDateTime assignmentTime= QDateTime::fromString(datetimeString, "yyyy-MM-dd HH:mm:ss");

        QDateTime currentDateTime = QDateTime::currentDateTime();

         qint64 secondsDiff = currentDateTime.secsTo(assignmentTime);

        if (secondsDiff >= 0 && secondsDiff < 7200) {
            QMessageBox::information(this, "Assignment Reminder",
                                     QString("Reminder: You have an assignment '%1' due on %2 at %3.")
                                         .arg(subject, date, time));
            return;
    }
}
}
void Dashboard::on_btnLogout_clicked()
{
    MainWindow *mainWindow;
    this->close();


     mainWindow=new MainWindow(this);
     mainWindow->show();
}


void Dashboard::on_btnIncomeAndExpense_clicked()
{
    IncomeAndExpense *incomeandexpense;
    this->hide();
    incomeandexpense=new IncomeAndExpense(userId,this);
    incomeandexpense->show();

}


void Dashboard::on_btnSetBudget_clicked()
{
    Budget *budget;
    this->hide();
    budget= new Budget(userId,this);
    budget->show();
}


void Dashboard::on_btnAcademic_clicked()
{
    Academic *academic;
    this->hide();
    academic= new Academic(userId,this);
    academic->show();
}


void Dashboard::on_btnFinancial_clicked()
{
    Report *report;
    this->hide();
    report= new Report(userId,this);
    report->show();

}

