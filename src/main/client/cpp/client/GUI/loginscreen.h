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
    QLabel *err_msg;


public slots:

    void SizeChanged(QSize);
    void LoginChecked();
    void UserNameAmend(QString);
    void PasswordAmend(QString);

signals:

    void NameChanged(QString);
    void LoginSucces();

};

#endif // LOGINSCREEN_H
