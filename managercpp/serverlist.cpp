#include "managerh/serverlist.h"
#include "ui_serverlist.h"

#include <QString>
#include <QModelIndex>
#include <QSqlQuery>
#include <QAbstractItemView>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
#include "extrah/delegate.h"
#include "managerh/checkserver.h"
Serverlist::Serverlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serverlist)
{
    ui->setupUi(this);
     setFixedSize(200,250);
     setWindowTitle(tr("服务生列表"));
     QString dbName="usrinfo.db";
     if(connect_to_database(dbName))
     {
         QSqlQuery query;
         query.exec("select *from serverlist");
         model.setColumnCount(1);
         model.setRowCount(10);
         ui->tableView->setModel(&model);
         ui->tableView->show();
         int i=0;
         while(query.next())
         {
             QModelIndex index=model.index(i,0,QModelIndex());
             model.setData(index,query.value(0).toString());
             i++;
         }
         ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
     }
}

Serverlist::~Serverlist()
{
    delete ui;
}

void Serverlist::on_pushButton_clicked()
{
    QString s=model.data(ui->tableView->currentIndex()).toString();
    s=s+"c";
    qDebug()<<s;
    Extern::man_ser_num=s;
    Checkserver *server=new Checkserver(this);
    server->exec();
}
