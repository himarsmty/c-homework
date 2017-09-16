#ifndef SYSSHOWUSERINFO_H
#define SYSSHOWUSERINFO_H

#include <QDialog>
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include <QModelIndex>
#include <QTimer>

namespace Ui {
class Sysshowuserinfo;
}

class Sysshowuserinfo : public QDialog
{
    Q_OBJECT

public:
    explicit Sysshowuserinfo(QWidget *parent = 0);
    ~Sysshowuserinfo();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void fresh();

private:
    Ui::Sysshowuserinfo *ui;
    QSqlRelationalTableModel *modela;
    QStandardItemModel model;
    QTimer *timer;

};

#endif // SYSSHOWUSERINFO_H
