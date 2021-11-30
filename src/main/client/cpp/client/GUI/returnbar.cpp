/**
 * @file returnbar.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class ReturnBar
 */
#include "returnbar.h"

#include "mainwindow.h"

#include <QGraphicsBlurEffect>

ReturnBar::ReturnBar(QWidget *parent) : QWidget(parent)
{
    setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    setStyleSheet(".ReturnBar{background-color: transparent;}");

    back_button = new QPushButton("Späť", this);
    back_button->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    back_button->setStyleSheet(
                "* {font: bold 'Arial Black'; font-size: 12pt; color: black; border-bottom-right-radius: 10px; background-color: rgba(0,255,0,180); image: url(../imgs/return_transparent.png);} \
                *::hover {border: 1.5px solid black; color: white; background-color: rgba(0,155,0,220);}");

    // create effects
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(1.5);
    back_button->setGraphicsEffect(blur);

    QObject::connect(back_button, SIGNAL(clicked()), parent, SLOT(stepBack()));
}

void ReturnBar::toggleDescription()
{
    if (back_button->text() == "")
        back_button->setText("Späť");
    else
        back_button->setText("");
}
