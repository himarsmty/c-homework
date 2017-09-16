#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Serverlist;
}

class Serverlist : public QDialog
{
    Q_OBJECT

public:
    explicit Serverlist(QWidget *parent = 0);
    ~Serverlist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Serverlist *ui;
    QStandardItemModel model;
};

#endif // SERVERLIST_H
