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
