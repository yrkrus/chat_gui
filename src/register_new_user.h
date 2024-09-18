#ifndef REGISTER_NEW_USER_H
#define REGISTER_NEW_USER_H

#include <QWidget>

namespace Ui {
class register_new_user;
}

class register_new_user : public QWidget
{
    Q_OBJECT

public:
    explicit register_new_user(QWidget *parent = nullptr);
    ~register_new_user();

private slots:
    void onReg();


private:
    Ui::register_new_user *ui;
    void createNewUser();
    void clearAllFields();

};

#endif // REGISTER_NEW_USER_H
