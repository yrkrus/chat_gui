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

SQL::StatusUser AuthWindow::getStatusUser()
{
    std::string login   = ui->edtLogin->text().toUtf8().toStdString();

    SQL::Base base;
    int curr_status = base.getUserCurrentStatus(login);

    switch (curr_status) {
        case 0: {
            return SQL::StatusUser::ENABLED;
            break;
        }
        case 1: {
            return SQL::StatusUser::ENABLED;
            break;
        }
        case 2: {
            return SQL::StatusUser::DISABLED;
            break;
        }
        case 3: {
            return SQL::StatusUser::BAN;
            break;
        }
    }
}

// авторизация
void AuthWindow::checkAuth()
{
    // проверки
    if (ui->edtLogin->text() == "" ) {

        MessageInfo msg("Пустое поле 'Логин'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtPwd->text() == "") {

        MessageInfo msg("Пустое поле 'Пароль'", MessageInfo::MessageType::Type_ERR);
        return;
    }

    std::string login   = ui->edtLogin->text().toUtf8().toStdString();
    std::string pwd     = ui->edtPwd->text().toUtf8().toStdString();

    SQL::Base base;

    if (!base.auth(login,pwd)) {
        MessageInfo msg_err("Ошибка авторизации, проверьте логин/пароль", MessageInfo::MessageType::Type_ERR);
        return;
    };

    // проверяем вдруг пользователь не может входить
    auto status = getStatusUser();
    if (status == SQL::StatusUser::DISABLED ) {

        MessageInfo msg_err("Пользователь отключен", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (status == SQL::StatusUser::BAN) {

        MessageInfo msg_err("Пользователь заблокирован", MessageInfo::MessageType::Type_ERR);
        return;
    }


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
