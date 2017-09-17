#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T19:26:24
#
#-------------------------------------------------

QT       += core gui

QT       +=sql

QT       +=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YRMS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    begincpp/login.cpp \
    begincpp/logup.cpp \
    syscpp/systemcontroler.cpp \
    servercpp/serverwindow.cpp \
    managercpp/managerwindow.cpp \
    chefcpp/chefwindow.cpp \
    usrcpp/menu.cpp \
    usrcpp/foodplate.cpp \
    usrcpp/pay.cpp \
    usrcpp/comment.cpp \
    usrcpp/chefcomment.cpp \
    usrcpp/servercomment.cpp \
    usrcpp/desk.cpp \
    extracpp/extern.cpp \
    usrcpp/customers.cpp \
    managercpp/checkchef.cpp \
    managercpp/checkserver.cpp \
    syscpp/sysshowuserinfo.cpp \
    managercpp/stuffnamelist.cpp \
    managercpp/serverlist.cpp

HEADERS += \
    beginh/login.h \
    beginh/logup.h \
    extrah/yrmssqlite.h \
    sysh/systemcontroler.h \
    serverh/serverwindow.h \
    managerh/managerwindow.h \
    chefh/chefwindow.h \
    usrh/menu.h \
    usrh/foodplate.h \
    usrh/pay.h \
    usrh/comment.h \
    extrah/delegate.h \
    usrh/chefcomment.h \
    usrh/servercomment.h \
    usrh/desk.h \
    extrah/extern.h \
    usrh/customers.h \
    managerh/checkchef.h \
    managerh/checkserver.h \
    sysh/sysshowuserinfo.h \
    managerh/stuffnamelist.h \
    managerh/serverlist.h

FORMS += \
    beginui/login.ui \
    beginui/logup.ui \
    sysui/systemcontroler.ui \
    serverui/serverwindow.ui \
    managerui/managerwindow.ui \
    chefui/chefwindow.ui \
    usrui/menu.ui \
    usrui/foodplate.ui \
    usrui/pay.ui \
    usrui/comment.ui \
    usrui/chefcomment.ui \
    usrui/servercomment.ui \
    usrui/desk.ui \
    usrui/customers.ui \
    managerui/checkchef.ui \
    managerui/checkserver.ui \
    sysui/sysshowuserinfo.ui \
    managerui/stuffnamelist.ui \
    managerui/serverlist.ui

DISTFILES +=

RESOURCES += \
    images.qrc
