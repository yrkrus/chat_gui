QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$quote(include\mysql)
LIBS  += $$quote(C:\c++\Chat\QT_final\gui_chat\include\mysql_lib\libmysql.lib)


SOURCES += \
    SQLResponce.cpp \
    authwindow.cpp \
    internalfunctions.cpp \
    main.cpp \
    mainwindow.cpp \
    messageinfo.cpp \
    register_new_user.cpp \
    users.cpp \
    userslist.cpp

HEADERS += \
    CONSTANTS.h \
    SQLResponce.h \
    authwindow.h \
    internalfunctions.h \
    mainwindow.h \
    messageinfo.h \
    register_new_user.h \
    users.h \
    userslist.h

FORMS += \
    authwindow.ui \
    mainwindow.ui \
    register_new_user.ui \
    userslist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

