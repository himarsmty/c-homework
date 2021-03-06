#include "usrh/servercomment.h"
#include "ui_servercomment.h"

#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"

Servercomment::Servercomment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Servercomment)
{
    ui->setupUi(this);
    setFixedSize(280,500);
    ui->horizontalSlider->setRange(0,10);
    ui->horizontalSlider->setValue(5);
    ui->slider->setRange(0,10);
    ui->slider->setValue(5);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
}

Servercomment::~Servercomment()
{
    delete ui;
}

void Servercomment::on_slider_valueChanged(int value)
{
    Servercomment::sval=ui->slider->value();
    QString s=QString("%1").arg( Servercomment::sval);
    s=s+"分";
    ui->lineEdit->setText(s);
}

void Servercomment::on_horizontalSlider_valueChanged(int value)
{
    Servercomment::effectiveness=ui->horizontalSlider->value();
    QString s=QString("%1").arg(Servercomment::effectiveness);
    s=s+"分";
    ui->lineEdit_2->setText(s);
}

void Servercomment::on_pushButton_clicked()
{
    int ds=QMessageBox::question(NULL,tr("提交"),tr("确定提交?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    switch (ds) {
    case QMessageBox::Yes:
    {
        if(Servercomment::sval==0||Servercomment::effectiveness==0)
        {
            int ok=QMessageBox::question(NULL,tr("来自服务生的请求"),tr("客官,您确定要打零分吗QAQ"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            switch (ok) {
            case QMessageBox::Yes:
            {
                QString dbName="usrinfo.db";
                QSqlQuery query;
                QString s=QString("%1").arg(Servercomment::sval);
                QString s1=QString("%1").arg(Servercomment::effectiveness);
                QString textstr=ui->textEdit->toPlainText();
                if(connect_to_database(dbName))
                {

                    QString si=Extern::servername+"c";
                    query.exec("insert into '"+si+"'(Score,Evaluate,number,effectiveness) Values('"+s+"','"+textstr+"','"+Extern::loginername+"','"+s1+"')");
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
            QString dbName="usrinfo.db";
            QSqlQuery query;
            QString s=QString("%1").arg(Servercomment::sval);
            QString s1=QString("%1").arg(Servercomment::effectiveness);
            QString textstr=ui->textEdit->toPlainText();
            if(connect_to_database(dbName))
            {
                QString si=Extern::servername+"c";
                query.exec("insert into '"+si+"'(Score,Evaluate,number,effectiveness) Values('"+s+"','"+textstr+"','"+Extern::loginername+"','"+s1+"')");
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
