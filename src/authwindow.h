#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H
#include <QMainWindow>
#include <QCloseEvent>
#include "SQLResponce.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();


signals:
    void loginSuccess();                                            // успешная авторизация
    void destr();                                                   // закроыте окна авторизации и открытие главной формы
    void sendAuthData(std::string login, std::string pwd);          // отправка учетных данных в главную форму
    void openFormRegistration();                                    // открыть форму регистрации нового пользователя

private:
    Ui::AuthWindow *ui;
    SQL::StatusUser getStatusUser();                                // проверка на статус пользователя (активен\не активен\бан)

public slots:
    void checkAuth();                                               // проверка авторизации
    void showFormRegistartion();                                    // открыть окно с регистрацией пользователя

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit destr();
        event->accept();
    }
};

#endif // AUTHWINDOW_H
