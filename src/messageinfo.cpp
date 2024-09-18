#include "messageinfo.h"
#include <QString>

MessageInfo::MessageInfo(std::string message, MessageType type) {

    msg = new QMessageBox;

    msg->setText(QString::fromStdString(message));

    if (type == Type_OK || type == Type_INFO) {
       msg->setIcon(QMessageBox::Information);
        msg->setWindowTitle("Информация");

    } else {
       msg->setIcon(QMessageBox::Critical);
        msg->setWindowTitle("Ошибка");
    }

    msg->setDefaultButton(QMessageBox::Ok);
    msg->exec();
}

MessageInfo::MessageInfo(std::string message, MessageType type, MYSQL *mysql)
{
    msg = new QMessageBox;

    msg->setText(QString::fromStdString(message) + "<br>" + QString::fromStdString(mysql_error(mysql) ));

    if (type == Type_OK || type == Type_INFO) {
        msg->setIcon(QMessageBox::Information);
        msg->setWindowTitle("Информация");

    } else {
        msg->setIcon(QMessageBox::Critical);
        msg->setWindowTitle("Ошибка");
    }

    msg->setDefaultButton(QMessageBox::Ok);
    msg->exec();
}

MessageInfo::~MessageInfo()
{
    delete(this->msg);
}
