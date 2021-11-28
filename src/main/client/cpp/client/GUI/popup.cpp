/**
 * @file popup.cpp
 * @author Samuel Hribik
 * @brief Contains implementation of Popup window defined in popup.h
 */

#include "popup.h"
#include "orderpreview.h"
#include "ordertab.h"
#include "mainwindow.h"

#include <QDebug>


/**
 * @brief Popup::Popup
 * @param parent - either OrderTab or OrderPreview
 * @brief Constructor of Popup
*/
Popup::Popup(QWidget * parent) : QWidget(parent) {



    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setFixedSize(340, 160);

    setStyleSheet(".Popup {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                        "background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #55EE55, stop:0 #999999);}");

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

Popup::~Popup(){

}

/**
 * @brief Popup::ButtonPressed : Destroys the Popup window after any button is pressed
 */
void Popup::ButtonPressed() {

    delete(this);
}
