#include "usrh/chefcomment.h"
#include "ui_chefcomment.h"

#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"

Chefcomment::Chefcomment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chefcomment)
{
    ui->setupUi(this);
    setFixedSize(280,500);
    ui->slider->setRange(0,10);
    ui->slider->setValue(5);
    ui->horizontalSlider->setRange(0,10);
    ui->horizontalSlider->setValue(5);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
}

Chefcomment::~Chefcomment()
{
    delete ui;
}

void Chefcomment::on_slider_valueChanged(int value)
{
    Chefcomment::sval=ui->slider->value();
    QString s=QString("%1").arg(Chefcomment::sval);
    s=s+"分";
    ui->lineEdit->setText(s);
}

void Chefcomment::on_horizontalSlider_valueChanged(int value)
{
    Chefcomment::effectiveness=ui->horizontalSlider->value();
    QString s=QString("%1").arg(Chefcomment::effectiveness);
    s=s+"分";
    ui->lineEdit_2->setText(s);
}

void Chefcomment::on_pushButton_clicked()
{
    qDebug()<<"slidervalue="<<Chefcomment::sval;
    int ds=QMessageBox::question(this,tr("提交"),tr("确定提交?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    switch (ds) {
    case QMessageBox::Yes:
    {
        if(Chefcomment::sval==0||Chefcomment::effectiveness==0)
        {
            int ok=QMessageBox::question(this,tr("来自厨师的请求"),tr("客官,您确定要打零分吗QAQ"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            switch (ok) {
            case QMessageBox::Yes:
            {
                QString dbName="/home/mty/DDDCPP/DATABASE/usrinfo.db";
                QSqlQuery query;
                QString s=QString("%1").arg(Chefcomment::sval);
                QString s1=QString("%1").arg(Chefcomment::effectiveness);
                qDebug()<<s;
                QString textstr=ui->textEdit->toPlainText();
                qDebug()<<textstr;
                if(connect_to_database(dbName))
                {
                    QString syu=Extern::chefname+"c";
                    query.exec("insert into '"+syu+"'(Score,Evaluate,number,effectiveness) Values('"+s+"','"+textstr+"','"+Extern::loginername+"','"+s1+"')");
                }
                this->close();
            }
                break;
            default:
                break;
            }
        }
        else
        {
            QString dbName="/home/mty/DDDCPP/DATABASE/usrinfo.db";
            QSqlQuery query;
            QString s=QString("%1").arg(Chefcomment::sval);
            QString s1=QString("%1").arg(Chefcomment::effectiveness);
            qDebug()<<s;
            QString textstr=ui->textEdit->toPlainText();
            qDebug()<<textstr;
            if(connect_to_database(dbName))
            {
                 QString syu=Extern::chefname+"c";
                query.exec("insert into '"+syu+"'(Score,Evaluate,number,effectiveness) Values('"+s+"','"+textstr+"','"+Extern::loginername+"','"+s1+"')");
            }
            this->close();
        }
    }
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}
