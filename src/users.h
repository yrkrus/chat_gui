#ifndef USERS_H
#define USERS_H

#include <string>

namespace USER {

    struct UserStruct
    {
        std::string login;			// логин
        std::string first_name;		// имя
        std::string last_name;		// фамилия
        int id{ 0 };				// id пользователя
        std::string pwd;
    };


    class CurrentUser
    {
        public:
            //CurrentUser() = delete;
            CurrentUser();
            CurrentUser(std::string &login, std::string &pwd);
            ~CurrentUser() = default;

            std::string getLogin()      const;
            std::string getFirstName()  const;
            std::string getLastName()   const;
            int         getID()         const;

            void setLogin(std::string &login);
            void setID(std::string &login, std::string &pwd);   // получаем текущий ID
            void setFirstName(int userID);
            void setLastName(int userID);


        protected:
            UserStruct user;
    };


    class NewUser : public UserStruct {

        public:
            NewUser() = default;
            ~NewUser() = default;

            UserStruct user;
    };


    class UList : public CurrentUser {
        public:
            UList() = default;
            ~UList() = default;

            int status;
            std::string last_logon;
            int userID;

    };

}




#endif // USERS_H
