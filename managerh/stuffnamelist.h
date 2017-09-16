#ifndef STUFFNAMELIST_H
#define STUFFNAMELIST_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Stuffnamelist;
}

class Stuffnamelist : public QDialog
{
    Q_OBJECT

public:
    explicit Stuffnamelist(QWidget *parent = 0);
    ~Stuffnamelist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Stuffnamelist *ui;
    QStandardItemModel model;
};

#endif // STUFFNAMELIST_H
