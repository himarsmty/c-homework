#include "managerh/checkchef.h"
#include "ui_checkchef.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAreaSeries>
#include <QtCharts>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
#include <QAbstractListModel>
#include <QValueAxis>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"

using namespace QtCharts;

Checkchef::Checkchef(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Checkchef)
{
    ui->setupUi(this);
    setFixedSize(790,450);
    setWindowTitle(Extern::man_chef_num);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);

    int n=0;
    QString dbName="usrinfo.db";
    QLineSeries *series=new QLineSeries();
    QLineSeries *series1=new QLineSeries();
    QStringListModel *model=new QStringListModel(this);
    QStringList List;
    if(connect_to_database(dbName))
    {

        QSqlQuery query;
        QString strchefamount=Extern::man_chef_num.left(Extern::man_chef_num.length()-1);
        query.exec("select *from '"+strchefamount+"'");
        query.next();
        QString chefam=query.value(0).toString();
        ui->lineEdit->setText(chefam);
        query.exec("select*from '"+Extern::man_chef_num+"'");
        while(query.next())
        {
            series->append(query.value(0).toInt(),query.value(1).toInt());
            series1->append(query.value(0).toInt(),query.value(4).toInt());
            n++;
            QString s1="用户:"+query.value(3).toString();
            QString s2="工作质量评分:"+query.value(1).toString();
            QString s4="工作效率评分"+query.value(4).toString();
            QString s3="评语:";
            List<<s1<<s2<<s4<<s3<<query.value(2).toString();
        }

    }
    model->setStringList(List);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

    QValueAxis *x=new QValueAxis;
    x->setMin(0);
    x->setMax(n);
    QValueAxis *y=new QValueAxis;
    y->setMin(0);
    y->setMax(11);

    QValueAxis *x1=new QValueAxis;
    QValueAxis *y1=new QValueAxis;
    x1->setRange(0,n);
    y1->setRange(0,11);

    QChart *chart=new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setAxisX(x,series);
    chart->setAxisY(y,series);
    chart->setTitle(tr("厨师工作质量打分折线图(x:次数,y:分数)"));

    QChart *chart1=new QChart();
    chart1->legend()->hide();
    chart1->addSeries(series1);
    chart1->setAxisX(x1,series1);
    chart1->setAxisY(y1,series1);
    x->setTickCount(n+1);
    x1->setTickCount(n+1);
    chart1->setTitle(tr("厨师工作效率打分折线图(x:次数,y:分数)"));


    QChartView *chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QChartView *chartview1=new QChartView(chart1);
    chartview1->setRenderHint(QPainter::Antialiasing);
    ui->scrollArea_2->setWidget(chartView);
    ui->scrollArea_3->setWidget(chartview1);
}


Checkchef::~Checkchef()
{
    delete ui;
}
