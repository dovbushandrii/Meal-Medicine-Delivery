/**
 * @file popup.cpp
 * @author Samuel Hribik
 * @brief Contains implementation of Popup window defined in popup.h
 */

#include "popup.h"
#include "orderpreview.h"
#include "ordertab.h"
#include "mainwindow.h"

#include <QPainter>
#include <QStyleOption>
#include <QDebug>


/**
 * @brief Popup::Popup
 * @param parent - either OrderTab or OrderPreview
 * @brief Constructor of Popup
*/
Popup::Popup(QWidget * parent, Typ typ) : QWidget(parent) {

/**
 * @brief Version of constructor for confirmation of the removal of an item
*/
if (typ == discard) {

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setFixedSize(340, 160);

    setStyleSheet(".Popup {border:1px solid black; background-color : rgba(165, 250, 165, 140)}");

    overall = new QVBoxLayout(this);
    lay = new QHBoxLayout();

    overall->setAlignment(Qt::AlignCenter);
    lay->setAlignment(Qt::AlignCenter);

    message = new QLabel();
    message->setText("Naozaj chcete odstrániť položku?");
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignCenter);
    message->setStyleSheet("* {font : bold 'Arial'; font-size : 16pt; border: 4px solid gray; border-radius: 10px;}");

    accept = new QPushButton();
    accept->setText("Ano");
    accept->setFixedSize(150, 50);
    accept->setStyleSheet("* {font : bold 'Arial Black'; border-radius: 10px;"
                                      "font-size: 16pt; background-color: rgba(0,0,0,40)} *::hover{background-color: rgba(0,0,0,100)}");

    decline = new QPushButton();
    decline->setText("Nie");
    decline->setFixedSize(150, 50);
    decline->setStyleSheet("* {font : bold 'Arial Black'; border-radius: 10px;"
                                      "font-size: 16pt; background-color: rgba(0,0,0,40)} *::hover{background-color: rgba(0,0,0,100)}");

    /**
     * @brief Comparison wether the parent is OrderTab or OrderPreivew,
     *        and adequately connects accept button with slot for the removal of item
    */
    if (dynamic_cast<OrderTab*>(parent) != nullptr) {
        QObject::connect(accept, SIGNAL(released()), dynamic_cast<OrderTab*>(parent), SLOT(deleteOrderItem()));
    }
    else if (dynamic_cast<OrderPreview*>(parent) != nullptr) {
        QObject::connect(accept, SIGNAL(released()), dynamic_cast<OrderPreview*>(parent), SLOT(deleteOrderItem()));
    }

    /**
     * @brief Connect both buttons with slot for closing the Popup window
     */
    QObject::connect(accept, SIGNAL(released()), this, SLOT(ButtonPressed()));
    QObject::connect(decline, SIGNAL(released()), this, SLOT(ButtonPressed()));

    lay->addWidget(accept);
    lay->addWidget(decline);

    overall->addWidget(message);
    overall->addLayout(lay);
}

/**
 * @brief Constructor version for creating new account
 */
else if (typ == regi) {

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setFixedSize(700, 500);

    setStyleSheet(".Popup {border:1px solid black; background-color : rgba(165, 250, 165, 140)}");

    overall = new QVBoxLayout(this);
    lay = new QHBoxLayout();

    overall->setAlignment(Qt::AlignCenter);
    lay->setAlignment(Qt::AlignCenter);

    message = new QLabel();
    message->setText("Prihlasovacie meno");
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignLeft);
    message->setStyleSheet("* {font : bold 'Arial'; font-size : 14pt;}");

    line = new QLineEdit();
    line->setFixedSize(600,60);
    line->setPlaceholderText("Prihlasovacie meno");
    line->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "font-size : 16pt;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    password = new QLabel();
    password->setText("Heslo");
    password->setWordWrap(true);
    password->setAlignment(Qt::AlignLeft);
    password->setStyleSheet("* {font : bold 'Arial'; font-size : 14pt;}");

    pass_line = new QLineEdit();
    pass_line->setFixedSize(600,60);
    pass_line->setEchoMode(QLineEdit::Password);
    pass_line->setPlaceholderText("Heslo");
    pass_line->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "font-size : 16pt;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    email = new QLabel();
    email->setText("Emailová adresa");
    email->setWordWrap(true);
    email->setAlignment(Qt::AlignLeft);
    email->setStyleSheet("* {font : bold 'Arial'; font-size : 14pt;}");

    email_line = new QLineEdit();
    email_line->setFixedSize(600,60);
    email_line->setPlaceholderText("Email");
    email_line->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "font-size : 16pt;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    QLabel *confirm = new QLabel();
    confirm->setText("Potvrdiť heslo");
    confirm->setWordWrap(true);
    confirm->setAlignment(Qt::AlignLeft);
    confirm->setStyleSheet("* {font : bold 'Arial'; font-size : 14pt;}");

    QLineEdit *confirm_line = new QLineEdit();
    confirm_line->setEchoMode(QLineEdit::Password);
    confirm_line->setFixedSize(600,60);
    confirm_line->setPlaceholderText("Potvrďte heslo");
    confirm_line->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                                            "font-size : 16pt;"
                                            "background-color: rgba(255, 255, 255, 120);"
                                            "border-radius: 10px;}");

    accept = new QPushButton();
    accept->setText("Vytvoriť");
    accept->setFixedSize(260, 60);
    accept->setStyleSheet("* {font : bold 'Arial Black'; border-radius: 10px;"
                                      "font-size: 16pt; background-color: rgba(0,0,0,40)} *::hover{background-color: rgba(0,0,0,100)}");

    decline = new QPushButton();
    decline->setText("Zrušiť");
    decline->setFixedSize(260, 60);
    decline->setStyleSheet("* {font : bold 'Arial Black'; border-radius: 10px;"
                                      "font-size: 16pt; background-color: rgba(0,0,0,40)} *::hover{background-color: rgba(0,0,0,100)}");


    /**
     * @brief Connect both buttons with slot for closing the Popup window
     */
    QObject::connect(accept, SIGNAL(released()), this, SLOT(ButtonPressed()));
    QObject::connect(decline, SIGNAL(released()), this, SLOT(ButtonPressed()));

    lay->addWidget(accept);
    lay->addWidget(decline);

    overall->addWidget(message);
    overall->addWidget(line);
    overall->addWidget(password);
    overall->addWidget(pass_line);
    overall->addWidget(confirm);
    overall->addWidget(confirm_line);
    overall->addWidget(email);
    overall->addWidget(email_line);
    overall->addLayout(lay);
}

}

Popup::~Popup(){

}

/**
 * @brief Popup::ButtonPressed : Destroys the Popup window after any button is pressed
 */
void Popup::ButtonPressed() {

    delete this;
}

void Popup::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
