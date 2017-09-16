#ifndef FOODPLATE_H
#define FOODPLATE_H

#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class Foodplate;
}

class Foodplate : public QDialog
{
    Q_OBJECT

public:
    explicit Foodplate(QWidget *parent = 0);
    ~Foodplate();
private:
    Ui::Foodplate *ui;
    QStandardItemModel model;
};

#endif // FOODPLATE_H
