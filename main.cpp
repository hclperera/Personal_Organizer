#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void createTables(){
    //users table
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT NOT NULL UNIQUE, "
                    "password TEXT NOT NULL)")) {
        qDebug() << "Failed to create user table:" << query.lastError().text();
    } else {
        qDebug() << "User Table verified or created successfully.";
    }


    //expense table
    if (!query.exec("CREATE TABLE IF NOT EXISTS expense ("
                    "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "date TEXT NOT NULL, "
                    "description TEXT NOT NULL, "
                    "category TEXT NOT NULL, "
                    "amount FLOAT NOT NULL, "
                    "uid INTEGER NOT NULL, "
                    "FOREIGN KEY(uid) REFERENCES users(id))")) {
        qDebug() << "Failed to create expense table:" << query.lastError().text();
    } else {
        qDebug() << "Expense table verified or created successfully.";
    }


    //income table
    if (!query.exec("CREATE TABLE IF NOT EXISTS income ("
                    "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "date TEXT NOT NULL, "
                    "source TEXT NOT NULL, "
                    "amount FLOAT NOT NULL, "
                    "uid INTEGER NOT NULL, "
                    "FOREIGN KEY(uid) REFERENCES users(id))")) {
        qDebug() << "Failed to create income table:" << query.lastError().text();
    } else {
        qDebug() << "Income table verified or created successfully.";
    }

    //budget table
    if (!query.exec("CREATE TABLE IF NOT EXISTS budget ("
                    "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "category TEXT NOT NULL, "
                    "month TEXT NOT NULL, "
                    "amount FLOAT NOT NULL, "
                    "uid INTEGER NOT NULL, "
                    "FOREIGN KEY(uid) REFERENCES users(id))")) {
        qDebug() << "Failed to create budget table:" << query.lastError().text();
    } else {
        qDebug() << "Budget table verified or created successfully.";
    }

    //academic table
    if (!query.exec("CREATE TABLE IF NOT EXISTS academic ("
                    "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "date TEXT NOT NULL, "
                    "time TEXT NOT NULL, "
                    "subject TEXT NOT NULL,"
                    "type TEXT NOT NULL, "
                    "uid INTEGER NOT NULL, "
                    "FOREIGN KEY(uid) REFERENCES users(id))")) {
        qDebug() << "Failed to create academic table:" << query.lastError().text();
    } else {
        qDebug() << "Academic table verified or created successfully.";
    }
}

bool createDatabaseConnection(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
    if(!db.open()){
        qDebug()<<"Unable To Connect to Database!"<<db.lastError().text();
            return false;
    }
    qDebug()<<"Database Connection Successfull!";
    createTables();
    return true;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    if(!createDatabaseConnection()){
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();


}
