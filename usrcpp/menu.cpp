#include "usrh/menu.h"
#include "ui_menu.h"

#include <QString>
#include "extrah/delegate.h"
#include "extrah/extern.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        menumodel=new QSqlTableModel(this);//new QSqlTableModel
        menumodel->setTable("Dishinfo");//model 选择打开table
        menumodel->setSort(2,Qt::AscendingOrder);//以单价顺序排列
        menumodel->select();//查找数据
        rowCount=menumodel->rowCount();//计算菜品总个数
        model.setColumnCount(4);//创建表格列数
        model.setRowCount(rowCount+2);//创建表格行数
        ui->tableview->setModel(&model);//显示表格（QTableView）
        SpinBoxDelegate *mydelegate=new SpinBoxDelegate(this);//new SpinBoxDelegate
        ui->tableview->setItemDelegate(mydelegate);//选择自己的代理模式
        ui->tableview->setGridStyle(Qt::DotLine);//点状显示间隔线
        ui->tableview->show();//显示表格
        ui->tableview->horizontalHeader()->setStretchLastSection(true);
        ui->tableview->setSelectionMode(QAbstractItemView::SingleSelection);//单独筛选
        ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);//按行显示

        for(int i=1;i<=rowCount;i++)//让数量和总价钱初始置位0
        {
            QModelIndex index=model.index(i,3,QModelIndex());
            model.setData(index,mydelegate->NoHint);
            index=model.index(i,2,QModelIndex());
            model.setData(index,mydelegate->NoHint);
        }
        ReadOnlyDelegate *readonlydelegate=new ReadOnlyDelegate;
        ui->tableview->setItemDelegateForColumn(2,mydelegate);//设置第三列为spinbox代理显示
        ui->tableview->setItemDelegateForColumn(0,readonlydelegate);//设置第一列为readonly
        ui->tableview->setItemDelegateForColumn(1,readonlydelegate);//设置第二列为readonly
        ui->tableview->setItemDelegateForRow(0,readonlydelegate);//设置第一行为readonly
        ui->tableview->setItemDelegateForColumn(3,readonlydelegate);//设置第四列为readonly
        ui->tableview->setItemDelegateForRow(rowCount+1,readonlydelegate);//设置最后一行为readonly
        /*填入菜品信息到表中*/
        QSqlQuery query;
        if(query.exec("select*from Dishinfo"))
        {
         QString foodname,foodprice;
            QModelIndex index=model.index(0,0,QModelIndex());
            model.setData(index,"菜名");
            index=model.index(0,1,QModelIndex());
            model.setData(index,"单价(元1)");
            index=model.index(0,2,QModelIndex());
            model.setData(index,"选择数量(份)");
            index=model.index(0,3,QModelIndex());
            model.setData(index,"总价(元)");
            int row=1;
            while(query.next())
            {
                int column=0;
                foodname=query.value(1).toString();
                foodprice=query.value(2).toString();
                int x=query.value(2).toInt();
                QModelIndex index=model.index(row,column,QModelIndex());
                model.setData(index,foodname);
                column++;
                index=model.index(row,column,QModelIndex());
                model.setData(index,foodprice);
                row++;
            }
        }
    }
}
Menu::~Menu()
{
    delete ui;
}

void Menu::on_ensureptn_clicked()
{
    int sum=0;
        QMap<QString,int>::iterator it;
    for(it=Extern::allloginer.begin();it!=Extern::allloginer.end();++it)
    {
        it.value()=0;
    }
    for(int row=1;row<=rowCount;row++)//计算总价钱
    {
        QModelIndex index=model.index(row,2,QModelIndex());
        QVariant amount(model.data(index));
        index=model.index(row,1,QModelIndex());
        QVariant singleprice(model.data(index));
        index=model.index(row,3,QModelIndex());
        model.setData(index,amount.toInt()*singleprice.toInt());
        QVariant sumprice(model.data(index));
        sum+=sumprice.toInt();
    }
    QModelIndex index=model.index(rowCount+1,3,QModelIndex());
    model.setData(index,sum);
    ordercount=0;
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        for(int row=1;row<=rowCount;row++)
        {
            QModelIndex index=model.index(row,2,QModelIndex());
            if(model.data(index).toInt()!=0)//如果这次点了该菜
            {
                index=model.index(row,0,QModelIndex());
                Menu::flag=1;
                query.exec("select*from '"+Extern::loginername+"'");
                while(query.next())//遍历已点菜品
                {
                    if(query.value(0).toString()==model.data(index).toString())//如果菜品已点,更新数据
                    {
                        Menu::flag=0;
                        QModelIndex index=model.index(row,2,QModelIndex());
                        int preamount=query.value(2).toInt();
                        preamount+=model.data(index).toInt();
                        int upstatus=query.value(5).toInt()+model.data(index).toInt();
                        QString z=QString("%1").arg(upstatus);
                        QString a=QString("%1").arg(preamount);
                        QString curname=query.value(0).toString();
                        query.exec("update '"+Extern::loginername+"' set amount='"+a+"'where name='"+curname+"'");
                        int prefullprice=query.value(3).toInt();
                        index=model.index(row,1,QModelIndex());
                        prefullprice=preamount*model.data(index).toInt();
                        QString b=QString("%1").arg(prefullprice);
                        query.exec("update '"+Extern::loginername+"' set fullprice='"+b+"' where name='"+curname+"'");
                        query.exec("update '"+Extern::loginername+"' set status='"+z+"' where name='"+curname+"'");
                    }
                }
                if(Menu::flag==1)
                {
                    QVariant o0,o1,o2,o3;//如果之前没有点过该菜则添加在最后一行
                    index=model.index(row,0,QModelIndex());//菜名
                    o0=model.data(index);
                    index=model.index(row,1,QModelIndex());//单价
                    o1=model.data(index);
                    index=model.index(row,2,QModelIndex());//数量
                    o2=model.data(index);
                    index=model.index(row,3,QModelIndex());//总价
                    o3=model.data(index);
                    query.exec("insert into '"+Extern::loginername+"'(name,singleprice,amount,fullprice,status) VALUES('"+o0.toString()+"','"+o1.toString()+"','"+o2.toString()+"','"+o3.toString()+"','"+o2.toString()+"')");
                }
            }
        }
    }
    QMessageBox::about(this,tr("点餐完毕"),tr("您可以继续选择打开菜单加菜或查看订单"));
    this->close();
}
