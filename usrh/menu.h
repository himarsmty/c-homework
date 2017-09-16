#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QAbstractItemView>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QModelIndex>
#include <QSpinBox>
#include <QObject>
#include <QSize>

#include "extrah/yrmssqlite.h"
#include "extrah/delegate.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    int rowCount;
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    int ordercount;
    int flag;
private:
    Ui::Menu *ui;
    QSqlTableModel *menumodel;//访问数据库数据
    QStandardItemModel model;
private slots:
    void on_ensureptn_clicked();
};

#endif // MENU_H
