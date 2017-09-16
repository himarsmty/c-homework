#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QDialog>

#include "usrh/menu.h"
#include "usrh/foodplate.h"
#include "usrh/pay.h"
#include "usrh/comment.h"
#include "usrh/desk.h"

namespace Ui {
class Customers;
}

class Customers : public QDialog
{
    Q_OBJECT

public:
    explicit Customers(QWidget *parent = 0);
    ~Customers();


private slots:

    void on_pushButton_clicked();

    void on_foodplatebtn_3_clicked();

    void on_menubtn_3_clicked();

    void on_paybtn_3_clicked();

    void on_commentbtn_3_clicked();

    void on_serchtablebtn_3_clicked();

    void on_callwaiterbtn_3_clicked();

    void on_checkdish_clicked();

private:
    Ui::Customers *ui;
    Menu *menuwindow;
    Foodplate *foodplatewindow;
    Pay *paywindow;
    Comment *commentwindow;
    Desk *newdesk;
};

#endif // CUSTOMERS_H
