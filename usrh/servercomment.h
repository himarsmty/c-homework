#ifndef SERVERCOMMENT_H
#define SERVERCOMMENT_H

#include <QDialog>

namespace Ui {
class Servercomment;
}

class Servercomment : public QDialog
{
    Q_OBJECT

public:
    explicit Servercomment(QWidget *parent = 0);
    ~Servercomment();

private slots:
    void on_pushButton_clicked();

    void on_slider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Servercomment *ui;
    int sval;
    int effectiveness;
};

#endif // SERVERCOMMENT_H
