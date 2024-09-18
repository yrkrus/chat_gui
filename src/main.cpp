#include "mainwindow.h"
#include "authwindow.h"
#include "register_new_user.h"
#include <QApplication>
#include <QtAlgorithms>
#include <QtWidgets>
#include <QString>
#include <stdio.h>
#include <iostream>
#include "userslist.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // окно авторизации
    AuthWindow authForm;
    authForm.show();

    // окно регистрации
    register_new_user regNewUser;
    QObject::connect(&authForm, &AuthWindow::openFormRegistration, [&]() {
        regNewUser.show();
    });

    // главная форма
    MainWindow homeForm;
    QObject::connect(&authForm, &AuthWindow::sendAuthData, &homeForm, &MainWindow::onSendAuthData);


    QObject::connect(&authForm, &AuthWindow::loginSuccess, [&]() {

        homeForm.show();
        homeForm.showMessage();
    });


    // показ всех пользователей
    UsersList userslist;
    QObject::connect(&homeForm, &MainWindow::openFormUsersList, [&]() {
        userslist.show();
        userslist.showUsersList();
    });


    QObject::connect(&authForm, &AuthWindow::destr, [&]() {
        authForm.close();

    });



    return app.exec();
}
