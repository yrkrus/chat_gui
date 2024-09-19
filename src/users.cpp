#include "users.h"
#include "SQLResponce.h"


// конструктор
USER::CurrentUser::CurrentUser(){}

USER::CurrentUser::CurrentUser(std::string &login, std::string &pwd)
{
    this->setLogin(login);
    this->setID(login,pwd);
    this->setFirstName(this->user.id);
    this->setLastName(this->user.id);

}

std::string USER::CurrentUser::getLogin() const
{
    return user.login;
}

std::string USER::CurrentUser::getFirstName() const
{
    return user.first_name;
}

std::string USER::CurrentUser::getLastName() const
{
    return user.last_name;
}

int USER::CurrentUser::getID() const
{
    return user.id;
}

void USER::CurrentUser::setLogin(std::string &login)
{
    this->user.login = login;
}

void USER::CurrentUser::setID(std::string &login, std::string &pwd)
{
    SQL::Base base;
    this->user.id = base.getUserID(login,pwd);

}

void USER::CurrentUser::setFirstName(int userID)
{
   SQL::Base base;
   this->user.first_name =  base.getUserFirstName(userID);
}

void USER::CurrentUser::setLastName(int userID)
{
    SQL::Base base;
    this->user.last_name = base.getUserLastName(userID);
}
