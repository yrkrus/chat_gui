#ifndef USERSLIST_H
#define USERSLIST_H

#include <QMainWindow>

namespace Ui {
class UsersList;
}

class UsersList : public QMainWindow
{
    Q_OBJECT

public:
    explicit UsersList(QWidget *parent = nullptr);
    ~UsersList();

    void showUsersList();   // отображение всех пользователей
    void showButtonStatus(); // текущее изменение статусов на кнопках

public slots:
    void onlistUsersclick(const QModelIndex &index);    // получение данных о том какой пользователь выбран в листе
    void onDisableEnableUser();                         // включение\отключение пользователя
    void onBanUnBanUser();                              // бан\разбан пользователя



private:
    Ui::UsersList *ui;



};

#endif // USERSLIST_H
