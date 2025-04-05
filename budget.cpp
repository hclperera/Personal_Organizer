#include "budget.h"
#include "ui_budget.h"
#include "dashboard.h"
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>


Budget::Budget(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Budget),userId(userId)
{
    ui->setupUi(this);
    ui->month->setDate(QDate::currentDate());
    showData();
}

Budget::~Budget()
{
    delete ui;
}

void Budget::insertData()
{
    QSqlQuery query(db);
    QString category=ui->cat_Budget->currentText();
    double amount=ui->amountBudget->value();
    QString month=ui->month->text();

    QSqlQuery checkquery(db);
    checkquery.prepare("SELECT id FROM budget WHERE uid=:uid AND month=:month AND category=:cat");
    checkquery.bindValue(":uid",userId);
    checkquery.bindValue(":month",month);
    checkquery.bindValue(":cat",category);

    if (!checkquery.exec()) {
        qDebug() << "Check query error:" << checkquery.lastError().text();
        return;
    }

    if(checkquery.next()){
        QMessageBox::warning(this, "Error", "Budget of selected Category for this month has already set.");
        return;
    }

    query.prepare("INSERT INTO budget(category,month,amount,uid) VALUES (:cat,:month,:amount,:uid)");
    query.bindValue(":cat",category);
    query.bindValue(":month",month);
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

void Budget::showData(){

    QSqlQuery query(db);
    query.prepare("SELECT id,category,month,amount FROM budget WHERE uid=:id");
    query.bindValue(":id",userId);
    if(!query.exec()){
        qDebug() <<"Show query error:" <<query.lastError().text();
        return;
    }

    ui->tableBudget->setRowCount(0);

    while(query.next())
    {
        int rowCount = ui->tableBudget->rowCount();
        ui->tableBudget->insertRow(rowCount);

        ui->tableBudget->setItem(rowCount,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableBudget->setItem(rowCount,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableBudget->setItem(rowCount,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableBudget->setItem(rowCount,3,new QTableWidgetItem(query.value(3).toString()));

    }
}
void Budget::clearAll(){
    ui->tableBudget->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("DELETE FROM budget WHERE uid=:id");
    query.bindValue(":id",userId);

    if(!query.exec()){
        qDebug()<<"Clear All Error :"<<query.lastError().text();
        return;
    }
    QMessageBox::information(this, "Sucess", "Table Cleared Sucessfully!");
    return;

}
void Budget::clearData(){
    int current=ui->tableBudget->currentRow();
    if(current<0){
        QMessageBox::warning(this, "Error", "No Row Selected");
        return;
    }

    QString id=ui->tableBudget->item(current,0)->text();
    QSqlQuery query(db);
    query.prepare("DELETE FROM budget WHERE uid=:id AND id=:num");
    query.bindValue(":id",userId);
    query.bindValue(":num",id);

    if(!query.exec()){
        qDebug()<<"Clear Record Error :"<<query.lastError().text();
        return;
    } else {
        ui->tableBudget->removeRow(current);
        QMessageBox::information(this, "Sucess", "Record Deleted Sucessfully!");
        return;
    }
}

void Budget::on_btnBack_2_clicked()
{
    this->close();

    Dashboard *dashboard = qobject_cast<Dashboard*>(parent());
    if (dashboard) {
        dashboard->show();
    }
}


void Budget::on_btnSelected_clicked()
{
    clearData();
}


void Budget::on_btnClearALL_clicked()
{
    clearAll();
}


void Budget::on_btnBudget_clicked()
{
    insertData();
    showData();
}

