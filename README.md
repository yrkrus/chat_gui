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
1. Тест1 (логин test пароль test)
2. Тест2 (логин test2 пароль 123)

Отсутствуют проверки
- уникальность логина
- проверка на сложность пароля
- статус пользователя (включен\выключен\бан)
- новые сообщения отображаются только не прочитанные, признак bool is_view в таблице message

ОПИСАНИЕ МОДУЛЕЙ  
authwindow
signals:
    void loginSuccess();                                            // успешная авторизация  
    void destr();                                                   // закроыте окна авторизации и открытие главной формы  
    void sendAuthData(std::string login, std::string pwd);          // отправка учетных данных в главную форму  
    void openFormRegistration();                                    // открыть форму регистрации нового пользователя  
public slots:  
    void checkAuth();                                               // проверка авторизации  
    void showFormRegistartion();                                    // открыть окно с регистрацией пользователя  

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
  
   private: 
    int errorCountConnections {0};                      // счетчик кол-ва не успешных подключений, после которого выходим из цикла while в reConnection  
    void createMySQLConnect(MYSQL &mysql);              // создание соединение с БД  
    void reConnection(int count);                       // переподключение к БД  

users  
класс пользователей с наследниками  

userslist  
список с пользователями  
