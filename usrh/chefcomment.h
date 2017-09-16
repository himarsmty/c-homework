#ifndef CHEFCOMMENT_H
#define CHEFCOMMENT_H

#include <QDialog>

namespace Ui {
class Chefcomment;
}

class Chefcomment : public QDialog
{
    Q_OBJECT

public:
    explicit Chefcomment(QWidget *parent = 0);
    ~Chefcomment();

private slots:
    void on_slider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Chefcomment *ui;
    int sval;
    int effectiveness;
};

#endif // CHEFCOMMENT_H
