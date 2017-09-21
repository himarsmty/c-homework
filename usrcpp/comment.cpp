#include "usrh/comment.h"
#include "ui_comment.h"

Comment::Comment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Comment)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);//显示最大化、最小化、关闭按钮
}

Comment::~Comment()
{
    delete ui;
}

void Comment::on_chefbtn_clicked()
{
    chefcom=new Chefcomment(this);
    chefcom->exec();

}

void Comment::on_serverbtn_clicked()
{
    servercom=new Servercomment(this);
    servercom->exec();
}
