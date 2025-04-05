#include "report.h"
#include "ui_report.h"
#include "dashboard.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Report::Report(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Report),userId(userId)
{
    ui->setupUi(this);
    ui->dateEdit->setDisplayFormat("yyyy-MM");
    ui->dateEdit->setDate(QDate::currentDate());
}

Report::~Report()
{
    delete ui;
}
void Report::INshowData(QString my){

    QSqlQuery iquery(db);
    iquery.prepare("SELECT source,amount FROM income WHERE uid=:id AND substr(date, 1, 7) = :month");
    iquery.bindValue(":id", userId);
    iquery.bindValue(":month", my);
    if (iquery.exec()){

        ui->incomeTable->setRowCount(0);
        while (iquery.next())
        {
            int rowCount = ui->incomeTable->rowCount();
            ui->incomeTable->insertRow(rowCount);

            ui->incomeTable->setItem(rowCount,0,new QTableWidgetItem(iquery.value(0).toString()));
            ui->incomeTable->setItem(rowCount,1,new QTableWidgetItem(iquery.value(1).toString()));
            //QString source=iquery.value(0).toString();
            //double iamount=iquery.value(1).toDouble();

        }
    }else{
        qDebug()<<"Error Getting Data(Report income)"<<iquery.lastError().text();
        return;
    }
}
void Report::EXshowData(QString my){
    QSqlQuery equery(db);
    equery.prepare("SELECT category,amount FROM expense WHERE uid=:id AND substr(date, 1, 7) = :month");
    equery.bindValue(":id", userId);
    equery.bindValue(":month", my);
    if (equery.exec()){

        ui->expenseTable->setRowCount(0);
        while (equery.next())
        {
            int rowCount = ui->expenseTable->rowCount();
            ui->expenseTable->insertRow(rowCount);

            ui->expenseTable->setItem(rowCount,0,new QTableWidgetItem(equery.value(0).toString()));
            ui->expenseTable->setItem(rowCount,1,new QTableWidgetItem(equery.value(1).toString()));

        }
    }else{
        qDebug()<<"Error Getting Data(Report income)"<<equery.lastError().text();
        return;
    }


}
void Report::displayMonthlyReport() {

    QString INmonthYear = ui->dateEdit->date().toString("yyyy/MM");
    QString EXmonthYear = ui->dateEdit->date().toString("yyyy-MM");
    qDebug()<<INmonthYear;
    qDebug()<<EXmonthYear;

    QSqlQuery query(db);
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double totalSavings = 0.0;

    query.prepare("SELECT SUM(amount) FROM income WHERE uid=:id AND substr(date, 1, 7) = :monthYear ");
    query.bindValue(":id", userId);
    query.bindValue(":monthYear", INmonthYear);
    if (query.exec() && query.next()) {
        totalIncome = query.value(0).toDouble();
        qDebug() << "Income query Sucessful";
    }

    query.prepare("SELECT SUM(amount) FROM expense WHERE uid=:id AND substr(date, 1, 7) = :monthYear");
    query.bindValue(":id", userId);
    query.bindValue(":monthYear", EXmonthYear);
    if (query.exec() && query.next()) {
        totalExpense = query.value(0).toDouble();
        qDebug() << "total Expense query Sucessful";
    }

    totalSavings = totalIncome - totalExpense;

        qDebug() << "total Expense "<<totalExpense;
        qDebug() << "total Income "<<totalIncome;
        qDebug() << "total Saving "<<totalSavings;

    ui->labelTotalIncome->setText(QString::number(totalIncome, 'f', 2));
    ui->labelTotalExpense->setText(QString::number(totalExpense, 'f', 2));
    ui->labelTotalSavings->setText(QString::number(totalSavings, 'f', 2));
    EXshowData(EXmonthYear);
    INshowData(INmonthYear);
}

void Report::on_btnBack_2_clicked()
{
    this->close();

    Dashboard *dashboard = qobject_cast<Dashboard*>(parent());
    if (dashboard) {
        dashboard->show();
    }
}


void Report::on_btnSubmit_clicked()
{
    displayMonthlyReport();
    qDebug() << "Displaying Monthly Report";
}

