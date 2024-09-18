#include "authwindow.h"
#include "ui_authwindow.h"
#include "SQLResponce.h"
#include "messageinfo.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register_new_user.h"
#include "ui_register_new_user.h"




#include <string>

AuthWindow::AuthWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    // скрываем под звездочки ввод
    ui->edtPwd->setEchoMode(QLineEdit::Password);


    // проверка авторизации (вход)
    connect(ui->btnAuth, SIGNAL(clicked(bool)), this, SLOT(checkAuth()));

    // регистрация нового пользователя
    connect(ui->btnRegister, SIGNAL(clicked(bool)), this, SLOT(showFormRegistartion()));


}

AuthWindow::~AuthWindow()
{
    delete ui;
}

// авторизация
void AuthWindow::checkAuth()
{
    std::string login   = ui->edtLogin->text().toUtf8().toStdString();
    std::string pwd     = ui->edtPwd->text().toUtf8().toStdString();

    SQL::Base base;

    if (!base.auth(login,pwd)) {
        MessageInfo msg_err("Ошибка авторизации, проверьте логин/пароль", MessageInfo::MessageType::Type_ERR);
        return;
    };


    // обновляем время захода
    if (!base.updateLoginSuccessTime(login,pwd)) {
        MessageInfo msg_err("Внутренняя ошибка, не удалось обновить данные", MessageInfo::MessageType::Type_ERR);
        return;
    }

    //MessageInfo msg_err("Авторизовались", MessageInfo::MessageType::Type_OK);

    emit loginSuccess();
    emit sendAuthData(login,pwd);
    emit destr();
}

void AuthWindow::showFormRegistartion()
{
    emit openFormRegistration();
}
