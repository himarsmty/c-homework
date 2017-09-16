#include <QApplication>

#include "beginh/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login dlg;
    if(dlg.exec())
    {
    return a.exec();
    }
    else return 0;
}
