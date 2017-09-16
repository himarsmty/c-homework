#ifndef MYQLIST_H
#define MYQLIST_H

#include <QString>

class Myqlist
{
public:
    struct Order
    {
        QString n_name;
        int n_singleprice;
        int n_amount;
        int n_fullprice;
    };
};

#endif // MYQLIST_H
