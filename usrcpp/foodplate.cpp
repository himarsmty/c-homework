#include "usrh/foodplate.h"
#include "ui_foodplate.h"

#include <QString>
#include <QModelIndex>
#include <QSqlQuery>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
#include "extrah/delegate.h"
Foodplate::Foodplate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Foodplate)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);//显示最大化、最小化、关闭按钮
    QString dbName="dishes.db";
    int n=0;//统计菜单总数
    if(connect_to_database(dbName))
    {
        QSqlQuery query0;
        query0.exec("select*from Dishinfo");
        while(query0.next())
        {
            n++;
        }
    }
    model.setColumnCount(4);
    model.setRowCount(n+2);
    ui->orderview->setModel(&model);
    ui->orderview->setGridStyle(Qt::DotLine);//点状显示间隔线
    ui->orderview->show();//显示表格
    QModelIndex index=model.index(0,0,QModelIndex());
    model.setData(index,"菜名");
    index=model.index(0,1,QModelIndex());
    model.setData(index,"单价(元)");
    index=model.index(0,2,QModelIndex());
    model.setData(index,"数量(份)");
    index=model.index(0,3,QModelIndex());
    model.setData(index,"总价(元)");
    int sum=0;
    if(connect_to_database(dbName))
    {
        int row=1;
        QSqlQuery query;
        query.exec("select*from '"+Extern::loginername+"'");
        while(query.next())
        {
            if(query.value(0)!="")
            {
                QModelIndex index=model.index(row,0,QModelIndex());
                model.setData(index,query.value(0));
                index=model.index(row,1,QModelIndex());
                model.setData(index,query.value(1));
                index=model.index(row,2,QModelIndex());
                model.setData(index,query.value(2));
                index=model.index(row,3,QModelIndex());
                model.setData(index,query.value(3));
                sum+=query.value(3).toInt();
                row++;
            }
        }
        index=model.index(row,3,QModelIndex());
        model.setData(index,sum);
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        for(int i=0;i<(n+2);i++)
        {
            ui->orderview->setItemDelegateForRow(i,readonlydelegate);
        }
    }
}

Foodplate::~Foodplate()
{
    delete ui;
}
