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


private:
    Ui::UsersList *ui;   
};

#endif // USERSLIST_H
