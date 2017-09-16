#ifndef PAY_H
#define PAY_H

#include <QDialog>
#include <QStandardItemModel>
#include "usrh/desk.h"

namespace Ui {
class Pay;
}

class Pay : public QDialog
{
    Q_OBJECT

public:
    explicit Pay(QWidget *parent = 0);
    ~Pay();
private slots:
    void on_payptn_clicked();

private:
    Ui::Pay *ui;
    QStandardItemModel model;
    int bill;
};

#endif // PAY_H
