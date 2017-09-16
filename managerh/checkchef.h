#ifndef CHECKCHEF_H
#define CHECKCHEF_H

#include <QDialog>

namespace Ui {
class Checkchef;
}

class Checkchef : public QDialog
{
    Q_OBJECT

public:
    explicit Checkchef(QWidget *parent = 0);
    ~Checkchef();

private:
    Ui::Checkchef *ui;
};

#endif // CHECKCHEF_H
