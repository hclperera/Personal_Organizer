#include "academic.h"
#include "ui_academic.h"
#include "dashboard.h"
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Academic::Academic(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Academic),userId(userId)
{
    ui->setupUi(this);
    showData();
}

Academic::~Academic()
{
    delete ui;
}

void Academic::insertData()
{
    QSqlQuery query(db);
    QString type=ui->type->currentText();
    QString subject=ui->subjectCombo->currentText();
    QString date=ui->dateEdit->text();
    QString time=ui->timeEdit->text();

    QSqlQuery checkquery(db);
    checkquery.prepare("SELECT id FROM academic WHERE uid=:uid AND subject=:subject AND type=:type "
                       "AND date=:date AND time=:time");
    checkquery.bindValue(":date",date);
    checkquery.bindValue(":time",time);
    checkquery.bindValue(":subject",subject);
    checkquery.bindValue(":type",type);
    checkquery.bindValue(":uid",userId);

    if (!checkquery.exec()) {
        qDebug() << "Check query error(acad):" << checkquery.lastError().text();
        return;
    }

    if(checkquery.next()){
        QMessageBox::warning(this, "Error", "You Cannot enter same entry twice!");
        return;
    }

    query.prepare("INSERT INTO academic(date,time,subject,type,uid) VALUES (:date,:time,:subject,:type,:uid)");
    query.bindValue(":date",date);
    query.bindValue(":time",time);
    query.bindValue(":subject",subject);
    query.bindValue(":type",type);
    query.bindValue(":uid",userId);

    if (!query.exec()) {
        qDebug() << "Insert query error:" << query.lastError().text();
        return;
    } else {
        QMessageBox::information(this, "Sucess", "Data Insertion Sucessfull!");
        return;

    }
}

void Academic::showData(){

    QSqlQuery query(db);
    query.prepare("SELECT id,date,time,subject,type FROM academic WHERE uid=:id");
    query.bindValue(":id",userId);
    if(!query.exec()){
        qDebug() <<"Show query error:" <<query.lastError().text();
        return;
    }

    ui->tableAcademic->setRowCount(0);

    while(query.next())
    {
        int rowCount = ui->tableAcademic->rowCount();
        ui->tableAcademic->insertRow(rowCount);

        ui->tableAcademic->setItem(rowCount,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableAcademic->setItem(rowCount,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableAcademic->setItem(rowCount,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableAcademic->setItem(rowCount,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableAcademic->setItem(rowCount,4,new QTableWidgetItem(query.value(4).toString()));

    }
}
void Academic::clearAll(){

    ui->tableAcademic->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("DELETE FROM academic WHERE uid=:id");
    query.bindValue(":id",userId);

    if(!query.exec()){
        qDebug()<<"Clear All Error :"<<query.lastError().text();
        return;
    }
    QMessageBox::information(this, "Sucess", "Table Cleared Sucessfully!");
    return;

}
void Academic::clearData(){
    int current=ui->tableAcademic->currentRow();
    if(current<0){
        QMessageBox::warning(this, "Error", "No Row Selected");
        return;
    }

    QString id=ui->tableAcademic->item(current,0)->text();
    QSqlQuery query(db);
    query.prepare("DELETE FROM academic WHERE uid=:id AND id=:num");
    query.bindValue(":id",userId);
    query.bindValue(":num",id);

    if(!query.exec()){
        qDebug()<<"Clear Record Error :"<<query.lastError().text();
        return;
    } else {
        ui->tableAcademic->removeRow(current);
        QMessageBox::information(this, "Sucess", "Record Deleted Sucessfully!");
        return;
    }
}

void Academic::on_btnClear_clicked()
{
    clearAll();
}


void Academic::on_btnSelected_clicked()
{
    clearData();
}


void Academic::on_btnSchedule_clicked()
{
    insertData();
    showData();
}


void Academic::on_btnBack_2_clicked()
{
    this->close();

    Dashboard *dashboard = qobject_cast<Dashboard*>(parent());
    if (dashboard) {
        dashboard->show();
    }
}

