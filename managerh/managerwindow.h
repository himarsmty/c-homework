#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>

namespace Ui {
class Managerwindow;
}

class Managerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Managerwindow(QWidget *parent = 0);
    ~Managerwindow();

private slots:
    void on_chefbtn_clicked();

    void on_serverptn_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Managerwindow *ui;
};

#endif // MANAGERWINDOW_H
