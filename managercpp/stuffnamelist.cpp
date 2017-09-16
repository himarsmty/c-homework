#include "managerh/stuffnamelist.h"
#include "ui_stuffnamelist.h"

#include <QString>
#include <QModelIndex>
#include <QSqlQuery>
#include <QAbstractItemView>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
#include "extrah/delegate.h"
#include "managerh/checkchef.h"

Stuffnamelist::Stuffnamelist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stuffnamelist)
{
    ui->setupUi(this);
    setFixedSize(200,250);
    setWindowTitle(tr("厨师列表"));
    QString dbName="/home/mty/DDDCPP/DATABASE/usrinfo.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("select *from cheflist");
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

Stuffnamelist::~Stuffnamelist()
{
    delete ui;
}

void Stuffnamelist::on_pushButton_clicked()
{
    QString s=model.data(ui->tableView->currentIndex()).toString();
    s=s+"c";
    qDebug()<<s;
    Extern::man_chef_num=s;
    Checkchef *chef=new Checkchef(this);
    chef->exec();
}
