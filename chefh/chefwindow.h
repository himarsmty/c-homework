#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTimer>
namespace Ui {
class Chefwindow;
}

class Chefwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Chefwindow(QWidget *parent = 0);
    ~Chefwindow();

private slots:
    void on_confirmbtn_clicked();
    void fresh();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Chefwindow *ui;
    QStandardItemModel model;
    QTimer *timer;
};

#endif // CHEFWINDOW_H
