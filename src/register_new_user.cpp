#include "register_new_user.h"
#include "ui_register_new_user.h"
#include "SQLResponce.h"
#include "messageinfo.h"
#include "users.h"

register_new_user::register_new_user(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::register_new_user)
{
    ui->setupUi(this);

    // скрываем под звездочки ввод
    ui->edtPwd->setEchoMode(QLineEdit::Password);
    ui->edtPwd2->setEchoMode(QLineEdit::Password);

    // регистрация нового пользователя
    connect(ui->btnReg, SIGNAL(clicked(bool)), this, SLOT(onReg()));
}

register_new_user::~register_new_user()
{
    delete ui;
}

void register_new_user::onReg()
{
    emit createNewUser();
}

void register_new_user::createNewUser()
{
    // проверки
    if (ui->edtFisrtName->text() == "") {

        MessageInfo msg("Пустое поле 'Имя'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtLastName->text() == "") {

        MessageInfo msg("Пустое поле 'Фамилия'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtLogin->text() == "") {

        MessageInfo msg("Пустое поле 'Логин'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtPwd->text() == "") {

        MessageInfo msg("Пустое поле 'Пароль'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtPwd2->text() == "") {

        MessageInfo msg("Пустое поле 'Подтверждение'", MessageInfo::MessageType::Type_ERR);
        return;

    } else if (ui->edtPwd->text() != ui->edtPwd2->text() ) {

        MessageInfo msg("Пароли не совпадают", MessageInfo::MessageType::Type_ERR);
        return;
    }


    // заводим нового пользователя
    SQL::Base base;

    USER::NewUser newuser;
    newuser.first_name  = ui->edtFisrtName->text().toUtf8().toStdString();
    newuser.last_name   = ui->edtLastName->text().toUtf8().toStdString();
    newuser.login       = ui->edtLogin->text().toUtf8().toStdString();
    newuser.pwd         = ui->edtPwd->text().toUtf8().toStdString();

    if (base.createNewUser(newuser)) {
            // очищаем поля
           clearAllFields();


            MessageInfo msg("Успешно зарегистрировано", MessageInfo::MessageType::Type_OK);
        } else {
            MessageInfo msg("Не удалось зарегистрировать", MessageInfo::MessageType::Type_ERR);
    }

}

void register_new_user::clearAllFields()
{
    ui->edtFisrtName->setText("");
    ui->edtLastName->setText("");
    ui->edtLogin->setText("");
    ui->edtPwd->setText("");
    ui->edtPwd2->setText("");
}
