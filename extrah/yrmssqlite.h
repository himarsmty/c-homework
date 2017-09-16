#ifndef YRMSSQLITE_H
#define YRMSSQLITE_H

#include <QString>
#include <QMessageBox>
#include <QTextEdit>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtDebug>

//#include <iostream>

static bool connect_to_database(QString &dbName)//连接数据库
{

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return false;
    }
    return 1;
}
static bool selectdata(QString &t_data,QString &input_pnumber,QString &input_pwd)//查找数据
{
    QSqlQuery query;
    if(query.exec(t_data))
    {
        QString data_num,data_pwd;
        while(query.next())
        {
            data_num=query.value(1).toString();
            data_pwd=query.value(2).toString();
            if(data_num==input_pnumber)
            {
                if(data_pwd==input_pwd)
                    return 1;
                else break;
            }
        }
        return 0;
    }
    return 0;
}

static bool ADD_usrdata(QString add_selectdata,QString &pnumber,QString &pwdnum)//插入数据
{
    QSqlQuery query;
    if(query.exec(add_selectdata))
    {
        QString sql = "insert into Users(Usernumber,Passward,Usertype) Values( '" + pnumber + "','" + pwdnum + "','顾客')";
        if(query.exec(sql))
        {
            qDebug()<<"logup new one";
            return 1;
        }
        else
        {
            qDebug()<<"User exist";
            return 0;
        }
    }
}
#endif // MYSQLITE_H
