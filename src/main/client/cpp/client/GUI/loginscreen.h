/**
 * @file loginscreen.h
 * @author Samuel Hribik
 * @brief Definitions of slots and signals for Login screen
 */


#ifndef LOGINSCREEN_H
#include <QDesktopWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "popup.h"
#include "mainwindow.h"

#define LOGINSCREEN_H

class LoginScreen : public QWidget
{
    Q_OBJECT

public:

    LoginScreen(QWidget *);
    ~LoginScreen();

private:

    QHBoxLayout *center;
    QVBoxLayout *box;
    QLineEdit *user_name;
    QLineEdit *password;
    QPushButton *login;
    QPushButton *reg;
    QLabel *err_msg;


public slots:

    void SizeChanged(QSize);
    void LoginChecked();
    void UserNameAmend(QString);
    void PasswordAmend(QString);
    void CreateRegister();


signals:

    void NameChanged(QString);
    void LoginSucces();

};

#endif // LOGINSCREEN_H
