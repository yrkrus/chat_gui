#include "userslist.h"
#include "ui_userslist.h"
#include "SQLResponce.h"
#include "users.h"
#include <QStandardItemModel>
#include "internalfunctions.h"
#include <QModelIndex>

UsersList::UsersList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UsersList)
{
    ui->setupUi(this);

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

