#ifndef LOGUP_H
#define LOGUP_H

#include <QDialog>

namespace Ui {
class Logup;
}

class Logup : public QDialog
{
    Q_OBJECT

public:
    explicit Logup(QWidget *parent = 0);
    ~Logup();

private:
    Ui::Logup *ui;
private slots:
    void logup();
};

#endif // LOGUP_H
