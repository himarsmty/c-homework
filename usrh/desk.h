#ifndef DESK_H
#define DESK_H

#include <QDialog>

namespace Ui {
class Desk;
}

class Desk : public QDialog
{
    Q_OBJECT

public:
    explicit Desk(QWidget *parent = 0);
    ~Desk();
private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::Desk *ui;
};
#endif // DESK_H
