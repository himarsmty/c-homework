#include "usrh/pay.h"
#include "ui_pay.h"

#include <QString>
#include <QModelIndex>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
#include "extrah/delegate.h"

int choisen;
Pay::Pay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pay)
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
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        for(int i=0;i<(n+2);i++)
        {
            ui->orderview->setItemDelegateForRow(i,readonlydelegate);
        }
        model.setData(index,sum);
        Pay::bill=sum;
    }

}

Pay::~Pay()
{
    delete ui;
}

void Pay::on_payptn_clicked()
{
    QString s=QString("%1").arg(Pay::bill);
    QString splus="您共消费"+s+"元,确定结账吗";
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        it.value()=0;
    }
    int cb=QMessageBox::question(this,tr("结账!"),splus,QMessageBox::No|QMessageBox::Yes,QMessageBox::No);
    switch (cb) {
    case QMessageBox::Yes:
    {
        QString dbNa="dishes.db";
        if(connect_to_database(dbNa))
        {
            QSqlQuery query0;
            query0.exec("drop table '"+Extern::loginername+"'");
        }
        QMessageBox::about(this,tr("已结账！"),tr("感谢您的光临!"));
        int release=Extern::choisen;
        Extern::choisen=0;
        QString s=QString("%1").arg(release);
        QString dbName="dishes.db";
        if(connect_to_database(dbName))
        {
            QSqlQuery query;
            query.exec("update Deskinfo set States=0 where Id='"+s+"'");
        }
    }
        break;
    case QMessageBox::No:
    default:
        break;
    }
}
