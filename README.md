исходный код располагается в ./src  

внешний каталог подключения ./include  
- mysql\mysql.h  
- mysql_lib\libmysql.lib  

  по умолчанию все подключения в CONSTANTS.h
- адрес БД
- порт БД
- логин БД
- пароль БД
- название БД

Чистая БД располагается в ./mysql_dump
предустановленные пользователи
1. Тест (логин test пароль test) - статус Active
2. Тест2 (логин test2 пароль 123) - статус Not_Active
3. Тест3 (логин test3 пароль 123)  - статус Banned

Отсутствуют проверки
- уникальность логина
- проверка на сложность пароля
- новые сообщения отображаются только не прочитанные, признак bool is_view в таблице message

##ОПИСАНИЕ МОДУЛЕЙ  

authwindow
signals:
    void loginSuccess();                                            // успешная авторизация  
    void destr();                                                   // закроыте окна авторизации и открытие главной формы  
    void sendAuthData(std::string login, std::string pwd);          // отправка учетных данных в главную форму  
    void openFormRegistration();                                    // открыть форму регистрации нового пользователя  
public slots:  
    void checkAuth();                                               // проверка авторизации  
    void showFormRegistartion();                                    // открыть окно с регистрацией пользователя  
private:   
SQL::StatusUser getStatusUser();                                // проверка на статус пользователя (активен\не активен\бан)   

CONSTANTS   
Константы  

internalfunctions  
std::string getCurrentDateTime();                                   // текущее время  
std::string getUserStatus(int status);                              // текущий статус пользователя  

mainwindow  
public slots:  
    void onSendAuthData(std::string login, std::string pwd);       // прередача текущих значений после авторизации  
    void onOpenFormUsersList();                                    // открытые списка с пользователями  
private slots:  
    void checkBD();                                                // тест проверка на соединение с БД  
    void sendMessage();                                            // отправка сообщения  

messageinfo  
генерация окна с сообщениями  

register_new_user  
регистрация нового пользователя  

SQLResponce  
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
   void changeStatusUser(std::string &login, StatusUser status);   // изменение состояние пользователя   
  
   private: 
    int errorCountConnections {0};                      // счетчик кол-ва не успешных подключений, после которого выходим из цикла while в reConnection  
    void createMySQLConnect(MYSQL &mysql);              // создание соединение с БД  
    void reConnection(int count);                       // переподключение к БД  

users  
класс пользователей с наследниками  

userslist  
    void showUsersList();   // отображение всех пользователей   
    void showButtonStatus(); // текущее изменение статусов на кнопках   
public slots:   
    void onlistUsersclick(const QModelIndex &index);    // получение данных о том какой пользователь выбран в листе   
    void onDisableEnableUser();                         // включение\отключение пользователя   
    void onBanUnBanUser();                              // бан\разбан пользователя   
