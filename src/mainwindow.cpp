#include <QApplication>
#include <QString>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QListView>
#include <QVariant>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SQLResponce.h"
#include "CONSTANTS.h"
#include "users.h"
#include <memory>
#include "messageinfo.h"
#include "authwindow.h"
#include "userslist.h"

//локальные
std::unique_ptr<USER::CurrentUser> current_user;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // для теста соединения с БД
    connect(ui->btnCheckBD, SIGNAL(clicked(bool)), this, SLOT(checkBD()));

    // отправка сообщения
    connect(ui->btnSendMessage, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));


    // открыть окно список пользователей
    connect(ui->btnUsersList, SIGNAL(clicked(bool)), this, SLOT(onOpenFormUsersList()));
    \

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage()
{

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    SQL::Base base;
    std::vector<SQL::Message> msg = base.showMessage();


    if (!msg.empty()) {

        QStandardItemModel *model = new QStandardItemModel(this);

        model->insertRows(0, msg.size());
        model->insertColumns(0, 1);

        for (size_t i=0; i<msg.size(); i++) {

            SQL::Base base;
            model->setData(model->index(i, 0), QString::fromStdString(msg[i].dateTimeMessage +" ("+base.getUserLogin(msg[i].userID)+")\t-> "+msg[i].message));

        }

        ui->listView_Message->setModel(model);

    }

    QGuiApplication::restoreOverrideCursor();
}

void MainWindow::onSendAuthData(std::string login, std::string pwd)
{

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);


    // создаем текущего залогиненного пользователя
    current_user = std::make_unique<USER::CurrentUser>(login,pwd);

    // показываем нашего залогиненного пользователя
    ui->lblCurrentUser->setText(QString::fromStdString(current_user->getLogin() + " > "));


    QGuiApplication::restoreOverrideCursor();

}

void MainWindow::onOpenFormUsersList()
{
    emit openFormUsersList();
}

void MainWindow::checkBD(){

    SQL::Base base;
    if (base.isConnected()) {

        ui->lblStatusBD->setText("ПОДКЛЮЧЕНО");

    } else {

        ui->lblStatusBD->setText("БД не подключена");

    }
}

// отправка ссобщения
void MainWindow::sendMessage()
{
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    SQL::Base base;
    if (base.isConnected()) {

        std::string message =  ui->textMessage->text().toUtf8().toStdString();
        base.sendNewMessage(current_user->getID(), SQL::NewMessageType::ALL,message);

        // очищаем написанное
        ui->textMessage->clear();
    }

    // обновляем написааное
    showMessage();



     QGuiApplication::restoreOverrideCursor();
}

