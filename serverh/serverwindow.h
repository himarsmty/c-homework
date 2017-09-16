#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class Serverwindow;
}

class Serverwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Serverwindow(QWidget *parent = 0);
    ~Serverwindow();

private slots:
    void on_chefbtn_clicked();

    void on_servebtn_clicked();

    void on_exitbtn_clicked();
    void fresh();

private:
    Ui::Serverwindow *ui;
    QTimer *timer;
};

#endif // SERVERWINDOW_H
