/**
 * @file loginscreen.cpp
 * @author Samuel Hribik
 * @brief Contains implementation of Login screen defined in loginscreen.h
 */

#include "popup.h"
#include "loginscreen.h"
#include "mainwindow.h"

#include <QDebug>
#include <QThread>

/**
 * @brief LoginScreen::LoginScreen
 * @param parent
 * @brief Constructor of LoginScreen
 */
LoginScreen::LoginScreen(QWidget *parent): QWidget(parent){


    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    setFixedSize(QSize(screen.width() * 0.8, screen.height() * 0.8));

    center = new QHBoxLayout(this);
    box = new QVBoxLayout();
    QHBoxLayout *button_layout = new QHBoxLayout();

    QFont lineFont("Arial", 22);
    QFont buttonFont("Arial Black", 16);

    user_name = new QLineEdit();
    user_name->setFixedSize(440,80);
    user_name->setFont(lineFont);
    user_name->setPlaceholderText("Prihlasovacie údaje");
    user_name->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    password = new QLineEdit();
    password->setFixedSize(440,80);
    password->setEchoMode(QLineEdit::Password);
    password->setFont(lineFont);
    password->setPlaceholderText("Heslo");
    password->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    /**
     * @brief Connection with slot to change color after unsuccesful login
     */
    QObject::connect(user_name, SIGNAL(textEdited(QString)), this, SLOT(UserNameAmend(QString)));
    QObject::connect(password, SIGNAL(textEdited(QString)), this, SLOT(PasswordAmend(QString)));

    err_msg = new QLabel();
    err_msg->setText("Nespravne udaje");
    err_msg->setStyleSheet("QLabel { background-color : yellow; color : red; }");
    err_msg->setFont(buttonFont);
    err_msg->hide();


    login = new QPushButton();
    login->setFixedSize(220,65);
    login->setFont(buttonFont);
    login->setText("Prihlásiť");
    login->setStyleSheet("QPushButton {  border: 2px solid gray;"
                                            "background-color: rgba(238, 252, 237, 160);"
                                            "border-radius: 10px;}");


    reg = new QPushButton();
    reg->setFixedSize(220,65);
    reg->setFont(buttonFont);
    reg->setText("Vytvoriť účet");
    reg->setStyleSheet("QPushButton {  border: 2px solid gray;"
                                            "background-color: rgba(238, 252, 237, 160);"
                                            "border-radius: 10px;}");

    QObject::connect(reg, SIGNAL(released()), this, SLOT(CreateRegister()));

    /**
     * @brief Connection with slot to check login information
     */
    QObject::connect(login, SIGNAL(clicked()), this, SLOT(LoginChecked()));

    box->setAlignment(Qt::AlignCenter);
    box->addWidget(user_name, 0, Qt::AlignCenter);
    box->addWidget(password, 0, Qt::AlignCenter);
    box->addWidget(err_msg, 0, Qt::AlignCenter);

    button_layout->setAlignment(Qt::AlignCenter);
    button_layout->addWidget(login, 0, Qt::AlignCenter);
    button_layout->addWidget(reg, 0, Qt::AlignHCenter);

    box->addLayout(button_layout);

    center->setAlignment(Qt::AlignCenter);
    center->addLayout(box);

    QObject::connect(this, SIGNAL(NameChanged(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(SizeChanged(QSize)));
    QObject::connect(this, SIGNAL(LoginSucces()), parent, SLOT(welcomeScreen()));

    setStyleSheet(".LoginScreen {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #55EE55, stop:0 #999999);}");

}

LoginScreen::~LoginScreen(){

}

void LoginScreen::CreateRegister() {
    Popup *window  = new Popup(nullptr, regi);
    window->show();
}

/**
 * @brief LoginScreen:LoginChecked : checks login information,
 *        and determines wether the login was - succesful -> emits signal to change Widget to welcomeScreen()
 *                                            - unsuccesful -> shows error massage and change colors of input Line Edits
 * @todo Replace string comparisons with functions to check the login information
*/
void LoginScreen::LoginChecked() {
    QThread::msleep(100);
    if (user_name->text() == "login" && password->text() == "heslo") {
        err_msg->hide();
        emit LoginSucces();
    }
    else {
        err_msg->show();
        user_name->setStyleSheet("QLineEdit {  border: 2px solid red;"
                                                "background-color: rgba(255, 0, 0, 160);"
                                                "border-radius: 10px;}");
        password->setStyleSheet("QLineEdit {  border: 2px solid red;"
                                                "background-color: rgba(255, 0, 0, 160);"
                                                "border-radius: 10px;}");
    }
}

/**
 * @brief LoginScreen::UserNameAmend
 * @param text
 * @brief Changes background color of user_name line edit and hides err_msg when rertying to login after an unsuccesful one
 */
void LoginScreen::UserNameAmend(QString text) {
    user_name->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
    err_msg->hide();
}

/**
 * @brief LoginScreen::PasswordAmend
 * @param text
 * @brief Changes background color of password line edit and hides err_msg when rertying to login after an unsuccesful one
 */
void LoginScreen::PasswordAmend(QString text) {
    password->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
    err_msg->hide();
}

void LoginScreen::SizeChanged(QSize size) {
    emit NameChanged("Prihlasovacie okno");
    setFixedSize(size);
}
