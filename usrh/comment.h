#ifndef COMMENT_H
#define COMMENT_H

#include <QDialog>
#include "usrh/chefcomment.h"
#include "usrh/servercomment.h"
namespace Ui {
class Comment;
}

class Comment : public QDialog
{
    Q_OBJECT

public:
    explicit Comment(QWidget *parent = 0);
    ~Comment();

private slots:
    void on_chefbtn_clicked();

    void on_serverbtn_clicked();

private:
    Ui::Comment *ui;
    Chefcomment *chefcom;
    Servercomment *servercom;
};

#endif // COMMENT_H
