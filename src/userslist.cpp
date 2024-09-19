#include "userslist.h"
#include "ui_userslist.h"
#include "SQLResponce.h"
#include "users.h"
#include <QStandardItemModel>
#include "internalfunctions.h"
#include "messageinfo.h"
#include <QModelIndex>


std::string current_user;
std::string current_status;

UsersList::UsersList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UsersList)
{
    ui->setupUi(this);


    // слоты

    // данные о выбранном пользователпе в листе
    connect(ui->listUsers, &QListView::clicked, this, &UsersList::onlistUsersclick);

    // отключение\включение пользователя
    connect(ui->btnEnableDisable, SIGNAL(clicked(bool)), this, SLOT(onDisableEnableUser()));

    // бан\разбан пользователя
     connect(ui->btnBan, SIGNAL(clicked(bool)), this, SLOT(onBanUnBanUser()));
}

UsersList::~UsersList()
{
    delete ui;
}

void UsersList::showUsersList()
{
    // создаем список с ткущими пользователями
    SQL::Base base;
    std::vector<USER::UList> users = base.createUsersList();

    if (users.empty()) { return; }

     QStandardItemModel *model = new QStandardItemModel(this);

    for (size_t i=0; i<users.size(); ++i) {

        model->insertRows(0, users.size());
        model->insertColumns(0, 1);

        for (size_t i=0; i<users.size(); i++) {
            model->setData(model->index(i, 0), QString::fromStdString(users[i].getLogin()+"\t"+users[i].last_logon+"\t"+INTERNALFUNCTIONS::getUserStatus(users[i].status)));
        }
    }

    ui->listUsers->setModel(model);
}

void UsersList::showButtonStatus()
{
    if (current_status == "ACTIVE") {

        ui->btnEnableDisable->setText("Отключить");
        ui->btnEnableDisable->setEnabled(true);

        ui->btnBan->setText("В бан");

    } else if (current_status == "NOT_ACTIVE") {

        ui->btnEnableDisable->setText("Включить");
        ui->btnEnableDisable->setEnabled(true);

        ui->btnBan->setText("В бан");

    } else if (current_status == "BANNED" ) {

        ui->btnBan->setText("Разбанить");
        ui->btnEnableDisable->setEnabled(false);

    }
}

void UsersList::onlistUsersclick(const QModelIndex &index)
{
    // найдем текущего пользователя (будем по логину его искать)
    QString data = index.data().toString();
    std::string user = data.toStdString();

    current_user = user.substr(0, user.find('\t'));

    // в зависимости от типа уз изменяем названия кнопочек
    current_status = user.substr(user.rfind('\t') + 1);

    // обновляем по кнопкам данные
    showButtonStatus();

}

void UsersList::onDisableEnableUser()
{
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    SQL::Base base;

    if (current_status == "ACTIVE" ) { // отключаем

        base.changeStatusUser(current_user, SQL::StatusUser::DISABLED);

    } else if (current_status == "NOT_ACTIVE") { // включаем

        base.changeStatusUser(current_user, SQL::StatusUser::ENABLED);
    }

    // обновляем по кнопкам
    showButtonStatus();

    // обновлем лист
    showUsersList();

    QGuiApplication::restoreOverrideCursor();
}

void UsersList::onBanUnBanUser()
{
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    SQL::Base base;

    if (current_status == "BANNED" ) { // разбаниваем

        base.changeStatusUser(current_user, SQL::StatusUser::UN_BAN);

    } else  { // баним

        base.changeStatusUser(current_user, SQL::StatusUser::BAN);
    }

    // обновляем по кнопкам
    showButtonStatus();

    // обновлем лист
    showUsersList();

    QGuiApplication::restoreOverrideCursor();
}
