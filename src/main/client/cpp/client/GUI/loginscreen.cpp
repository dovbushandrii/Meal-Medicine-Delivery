#include "loginscreen.h"
#include "mainwindow.h"

LoginScreen::LoginScreen(QWidget *parent): QWidget(parent){


    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    setFixedSize(QSize(screen.width() * 0.8, screen.height() * 0.8));

    center = new QHBoxLayout(this);
    box = new QVBoxLayout();

    user_name = new QLineEdit();
    user_name->setFixedSize(220,40);
    user_name->setText("Prihlasovacie meno");

    password = new QLineEdit();
    password->setFixedSize(220,40);
    password->setText("Heslo");

    login = new QPushButton();
    login->setText("Prihlásiť");
    QObject::connect(login, SIGNAL(clicked()), parent, SLOT(welcomeScreen()));

    box->setAlignment(Qt::AlignCenter);
    box->addWidget(user_name, 0, Qt::AlignCenter);
    box->addWidget(password, 0, Qt::AlignCenter);
    box->addWidget(login, 0, Qt::AlignCenter);

    center->setAlignment(Qt::AlignCenter);
    center->addLayout(box);

    QObject::connect(this, SIGNAL(NameChanged(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(SizeChanged(QSize)));

    setStyleSheet(".LoginScreen {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #55EE55, stop:0 #999999);}");


    emit NameChanged("Prihlasovacie okno");


}

LoginScreen::~LoginScreen(){

}



void LoginScreen::SizeChanged(QSize size) {
    setFixedSize(size);
}
