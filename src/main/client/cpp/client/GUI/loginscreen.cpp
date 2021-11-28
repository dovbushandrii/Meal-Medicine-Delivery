/**
 * @file loginscreen.cpp
 * @author Samuel Hribik
 * @brief Contains implementation of Login screen defined in loginscreen.h
 */

#include "loginscreen.h"
#include "mainwindow.h"

#include <QDebug>
#include <QThread>

LoginScreen::LoginScreen(QWidget *parent): QWidget(parent){


    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    setFixedSize(QSize(screen.width() * 0.8, screen.height() * 0.8));

    center = new QHBoxLayout(this);
    box = new QVBoxLayout();

    QFont lineFont("Arial", 18);
    QFont buttonFont("Arial Black", 16);

    user_name = new QLineEdit();
    user_name->setFixedSize(400,80);
    user_name->setFont(lineFont);
    user_name->setPlaceholderText("Prihlasovacie údaje");
    user_name->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
    QObject::connect(user_name, SIGNAL(textChanged(QString)), this, SLOT(UserNameAmend(QString)));

    password = new QLineEdit();
    password->setFixedSize(400,80);
    password->setFont(lineFont);
    password->setPlaceholderText("Heslo");
    password->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
    QObject::connect(password, SIGNAL(textChanged(QString)), this, SLOT(PasswordAmend(QString)));

    err_msg = new QLabel();
    err_msg->setText("Nespravne udaje");
    err_msg->setStyleSheet("QLabel { background-color : yellow; color : red; }");
    err_msg->setFont(buttonFont);
    err_msg->hide();


    login = new QPushButton();
    login->setFixedSize(250,65);
    login->setFont(buttonFont);
    login->setText("Prihlásiť");
    login->setStyleSheet("QPushButton {  border: 2px solid gray;"
                                            "background-color: rgba(238, 252, 237, 160);"
                                            "border-radius: 10px;}");
    QObject::connect(login, SIGNAL(clicked()), this, SLOT(LoginChecked()));

    box->setAlignment(Qt::AlignCenter);
    box->addWidget(user_name, 0, Qt::AlignCenter);
    box->addWidget(password, 0, Qt::AlignCenter);
    box->addWidget(err_msg, 0, Qt::AlignCenter);
    box->addWidget(login, 0, Qt::AlignCenter);

    center->setAlignment(Qt::AlignCenter);
    center->addLayout(box);

    QObject::connect(this, SIGNAL(NameChanged(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(SizeChanged(QSize)));
    QObject::connect(this, SIGNAL(LoginSucces()), parent, SLOT(welcomeScreen()));

    setStyleSheet(".LoginScreen {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #55EE55, stop:0 #999999);}");


    emit NameChanged("Prihlasovacie okno");


}

LoginScreen::~LoginScreen(){

}


void LoginScreen::LoginChecked() {
    QThread::msleep(200);
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

void LoginScreen::UserNameAmend(QString text) {
    user_name->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
}

void LoginScreen::PasswordAmend(QString text) {
    password->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");
}

void LoginScreen::SizeChanged(QSize size) {
    setFixedSize(size);
}
