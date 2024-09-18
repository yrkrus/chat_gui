#ifdef _WIN32
#include <include/mysql/mysql.h>
#elif __linux__
#include "mysql/mysql.h"
#endif


#include <string>
#include <QMessageBox>


#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

class MessageInfo
{
public:

    enum MessageType {
        Type_OK      = 0,
        Type_INFO    = 1,
        Type_ERR     = 2,
    };

    MessageInfo(std::string message, MessageType type);
    MessageInfo(std::string message, MessageType type, MYSQL *mysql);

    ~MessageInfo();

private:
    QMessageBox *msg;
};

#endif // MESSAGEINFO_H
