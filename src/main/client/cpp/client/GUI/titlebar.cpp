/**
 * @file titlebar.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class TitleBar
 */
#include "titlebar.h"

#include "mainwindow.h"

#include <QIcon>
#include <QSize>
#include <QGraphicsBlurEffect>

TitleBar::TitleBar(QWidget *parent, QApplication *app) : QWidget(parent)
{
    setFixedSize(3 * TITLE_WIDTH, TITLE_HEIGHT);    // 3 as there are 3 buttons
    layout = new QHBoxLayout(this);
    close = new QPushButton("Zavrieť", this);
    maximize = new QPushButton("Zväčšiť", this);
    minimize = new QPushButton("Skryť", this);

    close->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    maximize->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    minimize->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    close->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    maximize->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    minimize->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    close->setStyleSheet(
                        "* {font: bold 'Arial Black'; font-size: 11pt; color: black; border-bottom-left-radius: 11px; background-color: rgba(200,0,0,180); image: url(../imgs/close_transparent.png);} \
                        *::hover {border: 1.5px solid black; color: white; background-color: rgba(100,0,0,220);}");
    maximize->setStyleSheet(
                        "* {font: bold 'Arial Black'; font-size: 11pt; color: black; border-bottom-left-radius: 11px; background-color: rgba(0,200,0,180); image: url(../imgs/maximize_transparent.png);} \
                        *::hover {border: 1.5px solid black; color: white; background-color: rgba(0,100,0,220);}");
    minimize->setStyleSheet(
                        "* {font: bold 'Arial Black'; font-size: 11pt; color: black; border-bottom-left-radius: 11px; background-color: rgba(0,0,200,180); image: url(../imgs/minimize_transparent.png);} \
                        *::hover {border: 1.5px solid black; color: white; background-color: rgba(0,0,60,220);}");

    QGraphicsBlurEffect *blur_close = new QGraphicsBlurEffect;
    blur_close->setBlurRadius(1.5);
    QGraphicsBlurEffect *blur_maximize = new QGraphicsBlurEffect;
    blur_maximize->setBlurRadius(1.5);
    QGraphicsBlurEffect *blur_minimize = new QGraphicsBlurEffect;
    blur_minimize->setBlurRadius(1.5);
    close->setGraphicsEffect(blur_close);
    maximize->setGraphicsEffect(blur_maximize);
    minimize->setGraphicsEffect(blur_minimize);

    // set up layouts
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setDirection(QBoxLayout::RightToLeft);
    layout->setAlignment(Qt::AlignRight);

    layout->addWidget(close);
    layout->addWidget(maximize);
    layout->addWidget(minimize);

    setLayout(layout);

    QObject::connect(close, SIGNAL(clicked()), app, SLOT(quit()));
    QObject::connect(minimize, SIGNAL(clicked()), parent, SLOT(showMinimized()));
    QObject::connect(maximize, SIGNAL(clicked()), this, SLOT(Maximize()));
    QObject::connect(this, SIGNAL(toFullScreen()), parent, SLOT(fullScreen()));
}

void TitleBar::toggleDescription()
{
    if (close->text() == "")
    {
        close->setText("Zavrieť");
        maximize->setText("Zväčšiť");
        minimize->setText("Skryť");
    }
    else
    {
        close->setText("");
        maximize->setText("");
        minimize->setText("");
    }
}

void TitleBar::Maximize()
{
    emit toFullScreen();
}
