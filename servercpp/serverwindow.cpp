#include "serverh/serverwindow.h"
#include "ui_serverwindow.h"

#include <QMessageBox>
#include <QTimer>

#include "extrah/extern.h"
Serverwindow::Serverwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serverwindow)
{
    ui->setupUi(this);
    QString title="YRMS[服务生模式] "+Extern::servername+"已登录";
    setWindowTitle(title);
    setFixedSize(300,300);//设置窗口尺寸
    ui->servelinedit->setFocusPolicy(Qt::NoFocus);
    ui->cheflineedit->setFocusPolicy(Qt::NoFocus);
    ui->custmlineedit->setFocusPolicy(Qt::NoFocus);
    timer=new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(fresh()));
}

Serverwindow::~Serverwindow()
{
    delete ui;
}

void Serverwindow::on_chefbtn_clicked()
{
    QMessageBox::about(NULL,tr(" "),tr("已确认"));
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        it.value()=3;
    }
    Extern::server_confirm=1;
    ui->cheflineedit->setText("");
}

void Serverwindow::on_servebtn_clicked()
{
    Extern::customer_to_server=2;
    ui->servelinedit->setText("");
}

void Serverwindow::on_exitbtn_clicked()
{
    int db=QMessageBox::warning(this,tr("退出登录"),tr("确定退出登录?"),QMessageBox::Yes|QMessageBox::No);
    switch (db) {
    case QMessageBox::Yes:
        Extern::server_status=0;
            this->close();
        break;
    default:
        break;
    }

}
void Serverwindow::fresh()
{
    QString s=QString("%1").arg(Extern::choisen);
    QString s1=s+"号桌客人:";
    ui->custmlineedit->setText(s1);
    if(Extern::customer_to_server==1)
    {
        ui->servelinedit->setText(tr("收到顾客呼叫"));
    }
    QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        if(it.value()==2)
        {
            ui->cheflineedit->setText("有菜品做完!");
        }
    }
}
