#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showMessage();  // показ истории сообщений

private:
    Ui::MainWindow *ui;

signals:
     void openFormUsersList();

public slots:
    void onSendAuthData(std::string login, std::string pwd); // прередаем текущие значения
    void onOpenFormUsersList();


private slots:
    void checkBD();                 // тест проверка на соединение с БД
    void sendMessage();             // отправка сообщения


};
#endif // MAINWINDOW_H
