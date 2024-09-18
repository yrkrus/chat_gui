#ifndef INTERNALFUNCTIONS_H
#define INTERNALFUNCTIONS_H

#include <string>

namespace INTERNALFUNCTIONS {

    enum UserStatus{

        ACTIVE      = 1,
        NOT_ACTIVE  = 2,
        BANNED      = 3,
    };

std::string getCurrentDateTime();           // текущее время
std::string getUserStatus(int status);      // текущий статус

}



#endif // INTERNALFUNCTIONS_H
