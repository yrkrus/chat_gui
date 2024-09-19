#ifdef _WIN32
#include "include/mysql/mysql.h"
#elif __linux__
#include "mysql/mysql.h"
#endif

#include <string>
#include <vector>
#include "users.h"

#ifndef SQLRESPONCE_H
#define SQLRESPONCE_H

namespace SQL{

    enum NewMessageType {
        ALL = -1,
        SINGLE = 0,
    };

        struct Message {
            std::string dateTimeMessage;
            std::string message;
            int userID;
        };

        enum class StatusUser {
            ENABLED,        // включить
            DISABLED,       // выключить
            BAN,            // бан
            UN_BAN,         // разбан
        };

class Base{

        public:
            Base();                                                         // инициализация подключение
            ~Base();                                                        // закрытие подключение

            bool isConnected();                                             // проверка есть ли подключение к БД
            bool auth(std::string &login, std::string &pwd);                // авторизация
            bool updateLoginSuccessTime(std::string &login,
                                        std::string &pwd);                  // обновление времени захода

            int getUserID(std::string &login, std::string &pwd);            // получение ID пользователя
            std::string getUserFirstName(int UserID);                       // получение имени пользоваптеля
            std::string getUserLastName(int UserID);                        // получение фамилии пользователяЫ

            void sendNewMessage(int sender, int recipient, std::string &message);     // отправка сообщения
            std::vector<Message> showMessage();                               // получение списка со
            bool createNewUser(USER::NewUser &user);                        // создангие нового пользователя
            std::string getUserLogin(int UserID);                           // получение логина пользователя
            std::vector<USER::UList> createUsersList();                     // получение списка пользователей

            int getUserCurrentStatus(std::string &login);                   // получение текущего статуса пользователя
            void changeStatusUser(std::string &login, StatusUser status);  // изменение состояние пользователя

        private:
            MYSQL mysql;
            int errorCountConnections {0};                      // счетчик кол-ва не успешных подключений, после которого выходим из цикла while в reConnection

            void createMySQLConnect(MYSQL &mysql);              // создание соединение с БД
            void reConnection(int count);                       // переподключение к БД


    };
}



#endif // SQLRESPONCE_H
