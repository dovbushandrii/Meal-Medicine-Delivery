/**
 * @file settings.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class Settings
 */
#include "settings.h"

Settings::Settings(MainWindow *parent) : QWidget(parent)
{
    setFixedSize(10 * TITLE_WIDTH, 10 * TITLE_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".Settings {background-color: rgba(0,0,0,30); border-radius: 10px;}");

    descriptions = new QPushButton("Zobraz popis", this);
    descriptions->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    descriptions->setCheckable(true);
    descriptions->setStyleSheet("* {font-size: 7pt; color: black; border: 2px solid black; border-radius: 10px; background-color:green;}\
                                *::checked{background-color:red;}"
                            );

    QObject::connect(descriptions, SIGNAL(clicked()), parent, SLOT(toggleDescriptions()));

    layoutMain = new QHBoxLayout(this);
    layoutLeft = new QVBoxLayout();
    layoutRight = new QVBoxLayout();

    layoutMain->setSizeConstraint(QLayout::SetFixedSize);

    layoutLeft->setSizeConstraint(QLayout::SetFixedSize);
    layoutLeft->setSpacing(0);
    layoutLeft->setMargin(0);

    layoutRight->setSizeConstraint(QLayout::SetFixedSize);
    layoutRight->setSpacing(0);
    layoutRight->setMargin(0);

    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);

    layoutLeft->setAlignment(Qt::AlignTop);
    layoutLeft->addWidget(descriptions);
}

Settings::~Settings()
{

}
