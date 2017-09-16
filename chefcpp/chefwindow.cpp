#include "chefh/chefwindow.h"
#include "ui_chefwindow.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QModelIndex>
#include <QString>
#include <QMessageBox>
#include <QTimer>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
#include "extrah/delegate.h"

Chefwindow::Chefwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chefwindow)
{
    ui->setupUi(this);
    QString title="YRMS[厨师模式] "+Extern::chefname+"已登录";
    setWindowTitle(title);
    timer=new QTimer(this);
    timer->setInterval(100);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(fresh()));
    setFixedSize(350,500);//设置固定窗口尺寸
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    model.setColumnCount(3);
    model.setRowCount(50);
    model.setHeaderData(2,Qt::Horizontal,"全部选择");
    model.setHeaderData(0,Qt::Horizontal," ");
    model.setHeaderData(1,Qt::Horizontal," ");
}

Chefwindow::~Chefwindow()
{
    delete ui;
}

void Chefwindow::on_confirmbtn_clicked()
{
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        it.value()=1;
    }
    QMessageBox::about(NULL,tr("确认"),tr("已接单!"));
    QString dbName="/home/mty/DDDCPP/DATABASE/dishes.db";
    QSqlQuery query;
    if(connect_to_database(dbName))
    {
        for(int i=0;i<50;i++)
        {
            QModelIndex indexq=model.index(i,0,QModelIndex());
            QString m_name=model.data(indexq).toString();
            QModelIndex indexz=model.index(i,2,QModelIndex());
            if(model.data(indexz).toString()=="Y")
            {
                model.setData(indexz,"");
                QModelIndex indexf=model.index(i,1,QModelIndex());
                Extern::cur_finished_dish+=model.data(indexf).toInt();
                query.exec("update '"+Extern::loginername+"' set status='0' where name='"+m_name+"'");
            }
        }
        QString dtname="/home/mty/DDDCPP/DATABASE/usrinfo.db";
        if(connect_to_database(dtname))
        {
            query.exec("select*from '"+Extern::chefname+"'");
            query.next();
            int all_f_dish=query.value(0).toInt()+Extern::cur_finished_dish;
            QString str_all_f_dish=QString("%1").arg(all_f_dish);
            qDebug()<<"all_f_dish"<<all_f_dish;
            query.exec("update '"+Extern::chefname+"'set dishamount='"+str_all_f_dish+"'");
            Extern::cur_finished_dish=0;
        }
    }
}

void Chefwindow::fresh()//实时更新order
{
    QString dbName="/home/mty/DDDCPP/DATABASE/dishes.db";
    QSqlQuery query;
    int n=0;//统计菜品数量
    if(connect_to_database(dbName))
    {
        QMap<QString,int>::iterator it;
        for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
        {
            QString s=it.key();
            query.exec("select*from '"+s+"'");
            query.next();
            QModelIndex index=model.index(0,0,QModelIndex());
            model.setData(index,"桌号");
            index=model.index(n,1,QModelIndex());
            model.setData(index,query.value(4));
            n++;
            index=model.index(n,0,QModelIndex());
            model.setData(index,"菜名");
            index=model.index(n,1,QModelIndex());
            model.setData(index,"数量");
            index=model.index(0,2,QModelIndex());
            model.setData(index,"双击此列选菜");
            n++;
            while(query.next())
            {
                qDebug()<<"chef::status"<<query.value(5).toInt();
                index=model.index(n,0,QModelIndex());
                model.setData(index,query.value(0));
                index=model.index(n,1,QModelIndex());
                model.setData(index,query.value(5));
                n++;
            }
        }
        CheckBoxDelegate *checkboxdelegate=new CheckBoxDelegate();
        ui->orderview->setItemDelegateForColumn(2,checkboxdelegate);
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate();
        ui->orderview->setItemDelegateForColumn(0,readonlydelegate);
        ui->orderview->setItemDelegateForColumn(1,readonlydelegate);
        ui->orderview->setItemDelegateForRow(0,readonlydelegate);
        ui->orderview->setItemDelegateForRow(1,readonlydelegate);
        ui->orderview->setModel(&model);
        ui->orderview->setGridStyle(Qt::DotLine);
        ui->orderview->show();
    }
}

void Chefwindow::on_pushButton_clicked()
{
    QMessageBox::about(NULL,tr(" "),tr("已呼叫服务生"));
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        it.value()=2;
    }
}

void Chefwindow::on_pushButton_2_clicked()
{
    int db=QMessageBox::warning(this,tr("即将退出"),tr("您确定要退出吗?"),QMessageBox::Yes|QMessageBox::No);
    switch (db) {
    case QMessageBox::Yes:
        this->close();
        break;
    default:
        break;
    }
}
