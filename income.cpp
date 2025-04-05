#include "income.h"
#include "incomeandexpense.h"
#include "ui_income.h"
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Income::Income(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Income),userId(userId)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    showData();
}

Income::~Income()
{
    delete ui;
}

void Income::on_btnBack_2_clicked()
{
    this->close();

    IncomeAndExpense *incomeandexpense = qobject_cast<IncomeAndExpense*>(parent());
    if (incomeandexpense) {
        incomeandexpense->show();
    }
}
void Income::insertData()
{
    QSqlQuery query(db);
    QString source=ui->source_Income->currentText();
    double amount=ui->amountIncome->value();
    QString date=ui->dateEdit->text();

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Amount must be a positive number.");
        return;
    }

    query.prepare("INSERT INTO income(date,source,amount,uid) VALUES (:date,:source,:amount,:uid)");
    query.bindValue(":date",date);
    query.bindValue(":source",source);
    query.bindValue(":amount",amount);
    query.bindValue(":uid",userId);

    if (!query.exec()) {
        qDebug() << "Insert query error:" << query.lastError().text();
        return;
    } else {
        QMessageBox::information(this, "Sucess", "Data Insertion Sucessfull!");
        return;

    }
}

void Income::showData(){

    QSqlQuery query(db);
    query.prepare("SELECT id,date,source,amount FROM income WHERE uid=:id");
    query.bindValue(":id",userId);
    if(!query.exec()){
        qDebug() <<"Show query error:" <<query.lastError().text();
        return;
    }

    ui->tableIncome->setRowCount(0);

    while(query.next())
    {
        int rowCount = ui->tableIncome->rowCount();
        ui->tableIncome->insertRow(rowCount);

        ui->tableIncome->setItem(rowCount,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableIncome->setItem(rowCount,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableIncome->setItem(rowCount,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableIncome->setItem(rowCount,3,new QTableWidgetItem(query.value(3).toString()));

    }
}
void Income::clearAll(){
    ui->tableIncome->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("DELETE FROM income WHERE uid=:id");
    query.bindValue(":id",userId);

    if(!query.exec()){
        qDebug()<<"Clear All Error :"<<query.lastError().text();
        return;
    }
    QMessageBox::information(this, "Sucess", "Table Cleared Sucessfully!");
    return;

}
void Income::clearData(){
    int current=ui->tableIncome->currentRow();
    if(current<0){
        QMessageBox::warning(this, "Error", "No Row Selected");
        return;
    }

    QString id=ui->tableIncome->item(current,0)->text();
    QSqlQuery query(db);
    query.prepare("DELETE FROM income WHERE uid=:id AND id=:num");
    query.bindValue(":id",userId);
    query.bindValue(":num",id);

    if(!query.exec()){
        qDebug()<<"Clear Record Error :"<<query.lastError().text();
        return;
    } else {
        ui->tableIncome->removeRow(current);
        QMessageBox::information(this, "Sucess", "Record Deleted Sucessfully!");
        return;
    }
}
void Income::on_btnAdd_clicked()
{
    insertData();
    showData();


}


void Income::on_btnClear_clicked()
{
    clearAll();
}


void Income::on_btnSelected_clicked()
{
    clearData();
}

