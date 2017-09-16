#ifndef CHECKSERVER_H
#define CHECKSERVER_H

#include <QDialog>

namespace Ui {
class Checkserver;
}

class Checkserver : public QDialog
{
    Q_OBJECT

public:
    explicit Checkserver(QWidget *parent = 0);
    ~Checkserver();

private:
    Ui::Checkserver *ui;
};

#endif // CHECKSERVER_H
