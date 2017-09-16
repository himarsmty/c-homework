#ifndef SYSTEMCONTROLER_H
#define SYSTEMCONTROLER_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QHeaderView>

namespace Ui {
class Systemcontroler;
}

class Systemcontroler : public QDialog
{
    Q_OBJECT

private:
    int menuflag=0;//检查是否打开菜单
public:
    explicit Systemcontroler(QWidget *parent = 0);
    ~Systemcontroler();

private slots:
    void on_viewuserbtn_clicked();

    void on_addmenubtn_clicked();

    void on_deletemenubtn_clicked();

    void on_exitbtn_clicked();

private:
    Ui::Systemcontroler *ui;
    QStandardItemModel model;
};


#endif // SYSTEMCONTROLER_H
