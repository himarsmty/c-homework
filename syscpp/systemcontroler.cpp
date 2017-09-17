#include "sysh/systemcontroler.h"
#include "ui_systemcontroler.h"
#include "extrah/yrmssqlite.h"

#include <iostream>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QModelIndex>

#include "beginh/login.h"
#include "extrah/extern.h"
#include "sysh/sysshowuserinfo.h"

Systemcontroler::Systemcontroler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Systemcontroler)
{
    ui->setupUi(this);
    setFixedSize(700,500);//设置最大窗口尺寸
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    Extern::ctrl_menu_status=1;
    QString dbName="/home/mty/DDDCPP/DATABASE/dishes.db";
    if(connect_to_database(dbName))
    {
        model.setColumnCount(2);
        model.setRowCount(100);
        model.setHeaderData(0,Qt::Horizontal,"菜名");
        model.setHeaderData(1,Qt::Horizontal,"单价");
        QSqlQuery query;
        query.exec("select*from Dishinfo");
        int i=0;
        while(query.next())
        {
            QModelIndex index=model.index(i,0,QModelIndex());
            QModelIndex indez=model.index(i,1,QModelIndex());
            model.setData(index,query.value(1).toString());
            model.setData(indez,query.value(2).toInt());
            i++;
        }
        ui->tableView->setModel(&model);
        ui->tableView->show();
    }
}

Systemcontroler::~Systemcontroler()
{
    delete ui;
}

void Systemcontroler::on_viewuserbtn_clicked()//查看账户信息
{
    Sysshowuserinfo *sys=new Sysshowuserinfo(this);
    sys->show();
}

void Systemcontroler::on_addmenubtn_clicked()//提交更改
{
    QString dbName="/home/mty/DDDCPP/DATABASE/dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("drop table Dishinfo1");
        query.exec("drop table Dishinfo");
        query.exec("CREATE TABLE Dishinfo1(Id integer PRIMARY KEY,Dishname TEXT UNIQUE,Dishprice INTEGER)");
        for(int i=0;;i++)
        {
            QModelIndex index=model.index(i,0,QModelIndex());
            QModelIndex indez=model.index(i,1,QModelIndex());
            QString s=model.data(index).toString();
            QString sz=model.data(indez).toString();
            qDebug()<<s<<sz;
            if(s=="")break;
            query.exec("insert into Dishinfo1(Dishname,Dishprice) Values('"+s+"','"+sz+"')");
        }
        query.exec("alter table Dishinfo1 rename to Dishinfo");
    }
    QMessageBox::about(NULL,tr("完成修改"),tr("已提交!"));
}

void Systemcontroler::on_deletemenubtn_clicked()//删减菜品
{
    QString dbName="/home/mty/DDDCPP/DATABASE/dishes.db";
    if(connect_to_database(dbName))
    {
        int curRow=ui->tableView->currentIndex().row();
        model.removeRow(curRow);
    }
}


void Systemcontroler::on_exitbtn_clicked()
{
    int db=QMessageBox::warning(this,tr("即将退出"),tr("您确定要退出吗"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    switch (db) {
    case QMessageBox::Yes:
        this->close();
        break;
    default:
        break;
    }
}
