#ifndef EXTERN_H
#define EXTERN_H
#include <QString>
#include <QStringList>
#include <QMap>

class Extern
{
public:
    static int choisen;
    static QString loginername;
    static QMap<QString,int> allloginer;
    static int progress_value;
    static int loginfocus;
    static int check_desk_choosen;
    static int customer_to_server;
    static QString chefname;
    static QString servername;
    static QString managername;
    static int cur_finished_dish;//本次厨师完成的菜品数
    static int cur_users;//所有用户数
    static QString man_chef_num;//经理选中的查看厨师
    static QString man_ser_num;//经理选中的查看服务生
    static int cur_server_to_desk;
    static int server_status;
    static int ctrl_menu_status;
};


#endif // EXTERN_H
