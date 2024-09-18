#ifdef _WIN32
#include <include/mysql/mysql.h>
#elif __linux__
#include "mysql/mysql.h"
#endif

#include "SQLResponce.h"
#include "CONSTANTS.h"
#include "messageinfo.h"
#include "internalfunctions.h"
#include "users.h"

#include "QtGui"

// конструктор
SQL::Base::Base(){
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    createMySQLConnect(this->mysql);
    QGuiApplication::restoreOverrideCursor();
}

// деструктор
SQL::Base::~Base(){
    if (mysql_ping(&this->mysql) == 0) {
        mysql_close(&this->mysql);
    }
}


void SQL::Base::createMySQLConnect(MYSQL &mysql) {

    const char *host	= CONSTANTS::cHOST.c_str();
    const char *login	= CONSTANTS::cLOGIN.c_str();
    const char *pwd		= CONSTANTS::cPASSWORD.c_str();
    const char *bd		= CONSTANTS::cBD.c_str();


    if (mysql_init(&mysql) == nullptr)
    {
        // Если дескриптор не получен — выводим сообщение об ошибке
        MessageInfo msg("Error: can't create MySQL-descriptor", MessageInfo::MessageType::Type_ERR, &mysql);
        return;
    }

    if (!mysql_real_connect(&mysql, host, login, pwd, bd, NULL, NULL, 0))
    {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        MessageInfo msg("SQL::Base::createMySQLConnect -> Error: can't connect to database", MessageInfo::MessageType::Type_ERR, &mysql);
        return;
    };

    mysql_set_character_set(&mysql, "utf8");
}

// проверка сосстояния подключения
bool SQL::Base::isConnected(){
    return (mysql_ping(&this->mysql) == 0 ? true : false);
}

// автооризация
bool SQL::Base::auth(std::string &login, std::string &pwd)
{
    if (!isConnected()) { return false; }

    size_t hash_pwd = std::hash<std::string>()(login + "_" + pwd);

    const std::string query = "select count(login) from users where login = '" + login + "' and pwd = '"+std::to_string(hash_pwd) +"'";


    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        // ошибка считаем что есть запись
        return false;
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row = mysql_fetch_row(result);

    bool auth;
    std::stoi(row[0]) == 0 ? auth = false : auth = true;

    mysql_free_result(result);

    return auth;
}


// обновление времени захода
bool SQL::Base::updateLoginSuccessTime(std::string &login, std::string &pwd)
{
    if (!isConnected()) { return false; }

    size_t hash_pwd = std::hash<std::string>()(login + "_" + pwd);

    std::string query = "update users set last_login = '" + INTERNALFUNCTIONS::getCurrentDateTime() + "' where login = '" + login + "' and pwd = '"+std::to_string(hash_pwd)+"'";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (updateLoginSuccessTime) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return false;
    };

    mysql_close(&this->mysql);
    return true;
}

int SQL::Base::getUserID(std::string &login, std::string &pwd)
{
    if (!isConnected()) { return -1; }

    size_t hash_pwd = std::hash<std::string>()(login + "_" + pwd);

    std::string query = "select id from users where login = '" + login + "' and pwd = '"+std::to_string(hash_pwd)+"'";


    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        // ошибка считаем что есть запись
        MessageInfo msg_err("SQL::Base -> (getUserID) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return -1;
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row = mysql_fetch_row(result);

   // mysql_close(&this->mysql); тут возможно ннадо будет вкл. понаблюдать за утечкой коннектов в mysql

   return std::atoi(row[0]);
   //mysql_free_result(result);


}

std::string SQL::Base::getUserFirstName(int UserID)
{
     if (!isConnected()) { return "null"; }

     const std::string query = "select first_name from users where id = '" + std::to_string(UserID)+"'";

     if (mysql_query(&this->mysql, query.c_str()) != 0)
     {

         MessageInfo msg_err("SQL::Base -> (getUserFirstName) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
         return "null";
     }

     // результат
     MYSQL_RES *result = mysql_store_result(&this->mysql);
     MYSQL_ROW row = mysql_fetch_row(result);

     return row[0];

}

std::string SQL::Base::getUserLastName(int UserID)
{
    if (!isConnected()) { return "null"; }

    const std::string query = "select last_name from users where id = '" + std::to_string(UserID)+"'";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {

        MessageInfo msg_err("SQL::Base -> (getUserLastName) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return "null";
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row = mysql_fetch_row(result);

    return row[0];

}

void SQL::Base::sendNewMessage(int sender, int recipient, std::string &message)
{
    if (!isConnected()) { return; }

    std::string query = "insert into message (sender,recipient,msg) values ('"
                        + std::to_string(sender) + "','"
                        + std::to_string(recipient) + "','"
                        + message + "')";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (sendNewMessage) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return;
    }

}

// получение списка всех сообщений
std::vector<SQL::Message> SQL::Base::showMessage()
{
     std::vector<SQL::Message> msg;

    if (!isConnected()) { return msg; }

    const std::string query = "select msg_time,msg,sender from message where is_view ='0' and recipient = '-1' order by msg_time ASC";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (showMessage) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return msg;
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        std::string date_time, message;
        int userID;

        for (size_t i = 0; i < mysql_num_fields(result); ++i)
        {
            if (i == 0)
            {
                date_time = row[i];
            }
            else if (i == 1)
            {
                message = row[i];
            } else if (i == 2) {

                userID = std::atoi(row[i]);
            }
        }

        msg.push_back({date_time,message,userID});
    }

    mysql_free_result(result);
    mysql_close(&this->mysql);

    return msg;
}

bool SQL::Base::createNewUser(USER::NewUser &user)
{
    if (!isConnected()) { return false; }

    size_t hash_pwd = std::hash<std::string>()(user.login + "_" + user.pwd);

    std::string query = "insert into users (login,pwd,first_name,last_name,state) values ('"
                        + user.login + "','"
                        + std::to_string(hash_pwd) + "','"
                        + user.first_name + "','"
                        + user.last_name + "','"
                        + "1')";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (createNewUser) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return false;
    };

        return true;

}


std::string SQL::Base::getUserLogin(int UserID)
{
    if (!isConnected()) { return "null"; }

    const std::string query = "select login from users where id = '" + std::to_string(UserID)+"'";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (getUserLogin) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return "null";
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row = mysql_fetch_row(result);

    return row[0];

}

std::vector<USER::UList> SQL::Base::createUsersList()
{
    std::vector<USER::UList> ulist;

    if (!isConnected()) { return ulist; }

    const std::string query = "select * from users order by login ASC";

    if (mysql_query(&this->mysql, query.c_str()) != 0)
    {
        MessageInfo msg_err("SQL::Base -> (createUsersList) error ->"  + query, MessageInfo::MessageType::Type_ERR, &this->mysql);
        return ulist;
    }

    // результат
    MYSQL_RES *result = mysql_store_result(&this->mysql);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        USER::UList curr_user;

        for (size_t i = 0; i < mysql_num_fields(result); ++i)
        {
            if (i == 0)
            {
                curr_user.userID = std::atoi(row[i]);
            }
            else if (i == 1)
            {
                std::string login = row[i];
                curr_user.setLogin(login);

            } else if (i == 2) {

                curr_user.setFirstName(curr_user.userID);

            } else if (i == 4) {

                curr_user.setLastName(curr_user.userID);

            } else if (i == 5) {

                curr_user.last_logon = row[i];

            } else if (i == 6) {

                curr_user.status = std::atoi(row[i]);
            }
        }

        ulist.push_back(curr_user);
    }

    mysql_free_result(result);
    mysql_close(&this->mysql);

    return ulist;

}

void SQL::Base::reConnection(int count){

    while (!isConnected()) {
        createMySQLConnect(this->mysql);

        errorCountConnections++;

        if (errorCountConnections == count) {
            errorCountConnections = 0;
            return;
        }

        // ждем пару сек
        Sleep(2000);
    }

}
