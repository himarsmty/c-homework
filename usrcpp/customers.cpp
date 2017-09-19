#include "usrh/customers.h"
#include "ui_customers.h"

#include <QDialog>
#include <QDebug>

#include "extrah/extern.h"
#include "extrah/yrmssqlite.h"
#include <QSqlQuery>
Customers::Customers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customers)
{
    ui->setupUi(this);

    setFixedSize(800,500);//设置固定窗口尺寸
    setWindowFlag(Qt::WindowMinimizeButtonHint,true);
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    setWindowFlag(Qt::WindowMaximizeButtonHint,false);

    qDebug()<<"loginmame_Customers="<<Extern::loginername;
    ui->checkdishlineEdit->setPlaceholderText(tr("做菜进度"));
    ui->checkdishlineEdit->setFocusPolicy(Qt::NoFocus);
    ui->progressBar->setValue(0);
    QString s="欢迎您!"+Extern::loginername;
    setWindowTitle(s);
    QMessageBox::about(NULL,"欢迎光临","请先选择座位!");
    Desk *desk=new Desk(NULL);//必须先选餐桌
    desk->exec();
}

Customers::~Customers()
{
    delete ui;
}

void Customers::on_pushButton_clicked()
{
    int ds=QMessageBox::question(this,tr("退出主界面"),tr("确定退出?"),QMessageBox::Cancel|QMessageBox::Yes,QMessageBox::Cancel);
    switch (ds) {
    case QMessageBox::Yes:
    {
        QString dbNa="dishes.db";
        if(connect_to_database(dbNa))
        {
            QSqlQuery query0;
            query0.exec("drop table '"+Extern::loginername+"'");
        }
        QMessageBox::about(this,tr("来着店长的比心!"),tr("感谢您的光临!"));
        int release=Extern::choisen;
        Extern::choisen=0;
        QString s=QString("%1").arg(release);
        QString dbName="dishes.db";
        if(connect_to_database(dbName))
        {
            QSqlQuery query;
            query.exec("update Deskinfo set States='0' where Id='"+s+"'");
        }
        Extern::loginername="";
        Extern::allloginer.clear();
        this->close();
    }
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}

void Customers::on_foodplatebtn_3_clicked()
{
    ui->scrollareaviewpayorder->widget()->close();
    ui->scrollareaviewpayorder->takeWidget();
    foodplatewindow=new Foodplate(this);
    ui->scrollareaviewpayorder->setWidget(foodplatewindow);
    foodplatewindow->show();
    qDebug()<<"food plate show"<<endl;
}

void Customers::on_menubtn_3_clicked()
{
    ui->scrollareaviewpayorder->widget()->close();
    ui->scrollareaviewpayorder->takeWidget();
    menuwindow=new Menu(this);
    ui->scrollareaviewpayorder->setWidget(menuwindow);
    menuwindow->show();
    qDebug()<<"menu has showed (this wirtten in Customers.cpp//R30)"<<endl;
}

void Customers::on_paybtn_3_clicked()
{
    ui->scrollareaviewpayorder->widget()->close();
    ui->scrollareaviewpayorder->takeWidget();
    paywindow=new Pay(this);
    ui->scrollareaviewpayorder->setWidget(paywindow);
    paywindow->show();
}

void Customers::on_commentbtn_3_clicked()
{
    ui->scrollareaviewpayorder->widget()->close();
    ui->scrollareaviewpayorder->takeWidget();
    commentwindow=new Comment(this);
    ui->scrollareaviewpayorder->setWidget(commentwindow);
    commentwindow->show();
}

void Customers::on_serchtablebtn_3_clicked()
{
    newdesk=new Desk(NULL);
    newdesk->exec();
}

void Customers::on_callwaiterbtn_3_clicked()
{
    if(Extern::server_status==1)
    {
        Extern::server_status==0;
        QString dbName="usrinfo.db";
        if(connect_to_database(dbName))
        {
            QSqlQuery query;
            query.exec("select *from '"+Extern::servername+"'");
            query.next();
            int hi_seramount=query.value(0).toInt()+1;
            QString hi_seramountstr=QString("%1").arg(hi_seramount);
            query.exec("update '"+Extern::servername+"' set deskamount='"+hi_seramountstr+"'");
        }
    }
    if(Extern::customer_to_server==2)
    {
        QMessageBox::about(NULL,tr("发送成功"),tr("请求已发送."));
        Extern::customer_to_server=1;
    }
    else
    {
        QMessageBox::about(NULL,tr("您有一条来着服务员的消息:"),tr("已收到呼叫."));
        Extern::customer_to_server=1;
    }

}

void Customers::on_checkdish_clicked()
{
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        if(it.value()==1)
        {
            ui->checkdishlineEdit->setText(tr("做菜中"));
            ui->progressBar->setValue(66);
        }
        if(it.value()==2||Extern::server_confirm==1)
        {
            ui->checkdishlineEdit->setText(tr("已完成,送菜中"));
            ui->progressBar->setValue(100);
            Extern::server_confirm=0;
        }
    }
}
