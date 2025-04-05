#include "incomeandexpense.h"
#include "ui_incomeandexpense.h"
#include "dashboard.h"
#include "income.h"
#include "expense.h"

IncomeAndExpense::IncomeAndExpense(int userId,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IncomeAndExpense),userId(userId)
{
    ui->setupUi(this);
}

IncomeAndExpense::~IncomeAndExpense()
{
    delete ui;
}



void IncomeAndExpense::on_btnBack_2_clicked()
{
    this->close();

    Dashboard *dashboard = qobject_cast<Dashboard*>(parent());
    if (dashboard) {
        dashboard->show();
    }
}


void IncomeAndExpense::on_btnIncomeTracker_clicked()
{
    Income *income;
    this->hide();
    income=new Income(userId,this);
    income->show();
}


void IncomeAndExpense::on_btnExpenseTracker_clicked()
{
    Expense *expense;
    this->hide();
    expense=new Expense(userId,this);
    expense->show();
}

