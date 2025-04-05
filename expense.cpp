#include "expense.h"
#include "incomeandexpense.h"
#include "ui_expense.h"
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Expense::Expense(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Expense),userId(userId)
{
    ui->setupUi(this);
     ui->dateEdit->setDate(QDate::currentDate());
    showData();
}

Expense::~Expense()
{
    delete ui;
}

void Expense::on_btnBack_2_clicked()
{
    this->close();

    IncomeAndExpense *incomeandexpense = qobject_cast<IncomeAndExpense*>(parent());
    if (incomeandexpense) {
        incomeandexpense->show();
    }
}

double Expense::getExpense(const QString category,int month){
    QSqlQuery query(db);
    double totalExpense = 0.0;

    query.prepare("SELECT SUM(amount) FROM expense WHERE uid=:id AND category=:cat "
                  "AND strftime('%m', date) = :month");
    query.bindValue(":id",userId);
    query.bindValue(":cat",category);
    query.bindValue(":month",QString::number(month).rightJustified(2,'0'));

    if(!query.exec()){
        qDebug() <<"Query1 error:" <<query.lastError().text();
        return 0.0;
      }
    if(query.next()){
          totalExpense=query.value(0).isNull()? 0.0 : query.value(0).toDouble();
    }
    qDebug() << "Current Expense{getexpense}:" << totalExpense;
    return totalExpense;
}

double Expense::getBudget(const QString category,int month){

    QSqlQuery query(db);
    double budgetValue=0.0;

    //we have to change month(int) into a month(str)
    //this changes 4(int) into 04(str)
    QString strMonth = QString::number(month).rightJustified(2, '0');


    query.prepare("SELECT amount FROM budget WHERE uid=:id AND month=:month AND category=:cat");
    query.bindValue(":id",userId);
    query.bindValue(":month",strMonth);
    query.bindValue(":cat",category);

    if(!query.exec()){
        qDebug()<<"Query Error :"<<query.lastError().text();
        return 0.0;
    }

    if(query.next()){
        budgetValue=query.value(0).isNull()?0.0:query.value(0).toDouble();
    }
    return budgetValue;
}
void Expense::insertData()
{
    QSqlQuery query(db);
    QString category=ui->cat_Expense->currentText();
    double amount=ui->amountExpense->value();
    QString date=ui->dateEdit->date().toString("yyyy-MM-dd");
    QString description=ui->LineDescription->text();
    QDate d1=QDate::currentDate();
    int month=d1.month();

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Amount must be a positive number.");
        return;
    }

    if(description.isEmpty()){
        QMessageBox::warning(this, "Error", "Description can not be empty.");
        return;
    }

    double cExpense=getExpense(category,month);
    double cBudget=getBudget(category,month);
    double rBudget= cBudget - cExpense;

    qDebug() << "Current Expense:" << cExpense;
    qDebug() << "Current Budget:" << cBudget;
    qDebug() << "Remaining Budget:" << rBudget;

    if(cBudget <= 0.0) {
        QMessageBox::warning(this, "Error", "Budget is not provided.Please Enter Budget for This Category!");
        return;
    }
    if (amount > rBudget) {
        QMessageBox::warning(this, "Error", QString("Exceeds remaining budget! \nRemaining: %1").arg(rBudget));
        return;
    }

    query.prepare("INSERT INTO expense(date,description,category,amount,uid) VALUES (:date,:desc,:cat,:amount,:uid)");
    query.bindValue(":date",date);
    query.bindValue(":desc",description);
    query.bindValue(":cat",category);
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

void Expense::showData(){

    QSqlQuery query(db);
    query.prepare("SELECT id,date,description,category,amount FROM expense WHERE uid=:id");
    query.bindValue(":id",userId);
    if(!query.exec()){
        qDebug() <<"Show query error:" <<query.lastError().text();
        return;
    }

    ui->tableExpense->setRowCount(0);

        while(query.next())
        {
            int rowCount = ui->tableExpense->rowCount();
            ui->tableExpense->insertRow(rowCount);

            ui->tableExpense->setItem(rowCount,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableExpense->setItem(rowCount,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableExpense->setItem(rowCount,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableExpense->setItem(rowCount,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableExpense->setItem(rowCount,4,new QTableWidgetItem(query.value(4).toString()));

        }
}


void Expense::clearAll(){
    ui->tableExpense->setRowCount(0);

    QSqlQuery query(db);
    query.prepare("DELETE FROM expense WHERE uid=:id");
    query.bindValue(":id",userId);

    if(!query.exec()){
        qDebug()<<"Clear All Error :"<<query.lastError().text();
    return;
    }
    QMessageBox::information(this, "Sucess", "Table Cleared Sucessfully!");
    return;

}
void Expense::clearData(){
    int current=ui->tableExpense->currentRow();
    if(current<0){
        QMessageBox::warning(this, "Error", "No Row Selected");
        return;
    }

    QString id=ui->tableExpense->item(current,0)->text();
    QSqlQuery query(db);
    query.prepare("DELETE FROM expense WHERE uid=:id AND id=:num");
    query.bindValue(":id",userId);
    query.bindValue(":num",id);

    if(!query.exec()){
        qDebug()<<"Clear Record Error :"<<query.lastError().text();
        return;
    } else {
        ui->tableExpense->removeRow(current);
        QMessageBox::information(this, "Sucess", "Record Deleted Sucessfully!");
        return;
    }
}

void Expense::on_btnExpense_clicked()
{
    insertData();
    showData();
}


void Expense::on_btnClearALL_clicked()
{
    clearAll();
}


void Expense::on_btnSelected_clicked()
{
    clearData();
}

