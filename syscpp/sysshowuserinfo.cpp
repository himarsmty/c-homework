#include "sysh/sysshowuserinfo.h"
#include "ui_sysshowuserinfo.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QStandardItemModel>

#include "extrah/delegate.h"
#include "extrah/extern.h"
#include "extrah/yrmssqlite.h"
#include <QTimer>

Sysshowuserinfo::Sysshowuserinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sysshowuserinfo)
{
    ui->setupUi(this);
    setFixedSize(500,400);
    timer=new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(fresh()));
    {
        QString dbName="usrinfo.db";
        QSqlQuery query;
        int n=0;
        if(connect_to_database(dbName))
        {
            query.exec("select*from Users");
            while(query.next())
            {
                n++;
            }
        }
        QModelIndex index;
        model.setColumnCount(3);
        model.setRowCount(n);
        model.setHeaderData(0,Qt::Horizontal,"账号");
        model.setHeaderData(1,Qt::Horizontal,"密码");
        model.setHeaderData(2,Qt::Horizontal,"用户类型");
        ui->tableView->setModel(&model);
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QHeaderView *header=ui->tableView->horizontalHeader();
        header->setStretchLastSection(true);
        ui->tableView->show();
        int m=0;//统计顾客数量
        for(int i=0;;i++)
        {
            if(connect_to_database(dbName))
            {
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()=="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;//为下一行输入做准备
                        m++;
                    }
                }
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()!="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;
                    }
                }
                break;
            }
        }
        ComboBoxDelegate *comboxdelegate=new ComboBoxDelegate;
        ui->tableView->setItemDelegateForColumn(2,comboxdelegate);
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        for(int j=0;j<m;j++)
        {
            ui->tableView->setItemDelegateForRow(j,readonlydelegate);
        }
    }
}

Sysshowuserinfo::~Sysshowuserinfo()
{
    delete ui;
}

void Sysshowuserinfo::on_pushButton_clicked()
{

    {
        QString dbName="usrinfo.db";
        QSqlQuery query;
        int n=0;
        if(connect_to_database(dbName))
        {
            query.exec("select*from Users");
            while(query.next())
            {
                n++;
            }
        }
        QModelIndex index;
        model.setColumnCount(3);
        model.setRowCount(n);
        model.setHeaderData(0,Qt::Horizontal,"账号");
        model.setHeaderData(1,Qt::Horizontal,"密码");
        model.setHeaderData(2,Qt::Horizontal,"用户类型");
        ui->tableView->setModel(&model);
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QHeaderView *header=ui->tableView->horizontalHeader();
        header->setStretchLastSection(true);
        ui->tableView->show();
        int m=0;//统计顾客数量
        for(int i=0;;i++)
        {
            if(connect_to_database(dbName))
            {
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()=="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;//为下一行输入做准备
                        m++;
                    }
                }
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()!="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;
                    }
                }
                break;
            }
        }
        ComboBoxDelegate *comboxdelegate=new ComboBoxDelegate;
        ui->tableView->setItemDelegateForColumn(2,comboxdelegate);
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        for(int j=0;j<m;j++)
        {
            ui->tableView->setItemDelegateForRow(j,readonlydelegate);

        }
        model.insertRow(n);
    }
}

void Sysshowuserinfo::on_pushButton_2_clicked()
{
    QString dbName="usrinfo.db";
    QSqlQuery query;
    int flag=0;//是否遍历所有的标志
    QString sq,sw,se;
    if(connect_to_database(dbName))
    {
        query.exec("CREATE TABLE Usersq(Id integer PRIMARY KEY,Usernumber text UNIQUE,Passward text NOT NULL, Usertype TEXT)");
        for(int row=0;;row++)
        {
            int column=0;
            for(int i=0;i<1;i++)
            {
                QModelIndex index=model.index(row,column,QModelIndex());
                column++;
                sq=model.data(index).toString();
                if(sq=="")//若遍历完
                {
                    flag=1;break;
                }
                index=model.index(row,column,QModelIndex());
                column++;
                sw=model.data(index).toString();
                index=model.index(row,column,QModelIndex());
                column++;
                se=model.data(index).toString();

            }
            if(flag==1)break;
            else{
                query.exec("insert into Usersq(Usernumber,Passward,Usertype) Values('"+sq+"','"+sw+"','"+se+"')");
            }
        }
        query.exec("drop table Users");
        query.exec("alter table Usersq rename to Users");
        query.exec("select *from Users");
        for(int i=0;i<=Extern::cur_users;i++)
        {
            query.next();
        }
        if(query.value(3)=="厨师")
        {
            QString sc=query.value(1).toString();
            query.exec("create table '"+sc+"'(dishamount integer)");
            query.exec("insert into '"+sc+"'(dishamount) VALUES('0')");
            query.exec("insert into cheflist(number) VALUES('"+sc+"')");
            sc.append("c");
            query.exec("create table '"+sc+"'(Id integer primary key,Score integer,Evaluate text,number text,effectiveness integer)");
        }
        if(query.value(3)=="服务生")
        {
            QString s=query.value(1).toString();
            query.exec("create table '"+s+"'(deskamount integer)");
            query.exec("insert into '"+s+"'(deskamount) Values('0')");
            query.exec("insert into serverlist(number) VALUES('"+s+"')");
            s.append("c");
            query.exec("CREATE TABLE '"+s+"'(Id integer primary key,Score integer,Evaluate text,number text,effectiveness integer)");
        }
        QMessageBox::about(NULL,tr("提交成功"),tr("已提交修改"));
    }
}

void Sysshowuserinfo::on_pushButton_4_clicked()
{
    {
        QString dbName="usrinfo.db";
        QSqlQuery query;
        int n=0;
        if(connect_to_database(dbName))
        {
            query.exec("select*from Users");
            while(query.next())
            {
                n++;
            }
        }
        QModelIndex index;
        model.setColumnCount(3);
        model.setRowCount(n);
        model.setHeaderData(0,Qt::Horizontal,"账号");
        model.setHeaderData(1,Qt::Horizontal,"密码");
        model.setHeaderData(2,Qt::Horizontal,"用户类型");
        ui->tableView->setModel(&model);
        QHeaderView *header=ui->tableView->horizontalHeader();
        header->setStretchLastSection(true);
        ui->tableView->show();
        int m=0;//统计顾客数量
        for(int i=0;;i++)
        {
            if(connect_to_database(dbName))
            {
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()=="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;//为下一行输入做准备
                        m++;
                    }
                }
                query.exec("select*from Users");
                while(query.next())
                {
                    if(query.value(3).toString()!="顾客")
                    {
                        for(int j=0;j<3;j++)
                        {
                            index=model.index(i,j,QModelIndex());
                            model.setData(index,query.value(j+1).toString());
                        }
                        i++;
                    }
                }
                break;
            }
        }
        ComboBoxDelegate *comboxdelegate=new ComboBoxDelegate;
        ui->tableView->setItemDelegateForColumn(2,comboxdelegate);
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        for(int j=0;j<m;j++)
        {
            ui->tableView->setItemDelegateForRow(j,readonlydelegate);
        }
    }
    QMessageBox::about(NULL,tr("刷新成功!"),tr("已刷新成功!"));
}
void Sysshowuserinfo::fresh()
{
    QString dbName="usrinfo.db";
    QSqlQuery query;
    int n=0;
    if(connect_to_database(dbName))
    {
        query.exec("select*from Users");
        while(query.next())
        {
            n++;
        }
        Extern::cur_users=n;
    }
}
