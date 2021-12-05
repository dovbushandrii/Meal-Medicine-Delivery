/**
 * @file infopanel.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class InfoPanel
 */
#include "infopanel.h"

#include <QDebug>

InfoPanel::InfoPanel(QWidget *parent, long id) : QWidget(parent)
{
    QObject::connect(this, SIGNAL(switchContent_s()), parent, SLOT(switchContent()));
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(parent, SIGNAL(updateTime_s()), this, SLOT(updateTime()));

    timePanel = new QLabel(dateTime.currentDateTime().toString("H:mm:ss dd.MM.yyyy"), this);
    timePanel->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT);
    timePanel->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 15pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");

    mainPanel = new QWidget(parent);
    supportPanel = new QLabel("Telefónne číslo na podporu\nxxxx xxx xxx", this);
    mainPanel->setStyleSheet(".QWidget {border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");
    supportPanel->setStyleSheet("* {font : 'Arial'; qproperty-alignment: AlignCenter; font-size: 12.5pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");

    layoutMiddle = new QVBoxLayout(mainPanel);
    layoutMiddle->setSpacing(0);
    layoutMiddle->setMargin(0);
    layoutMiddle->setAlignment(Qt::AlignTop);

    personalDetails = new QLabel(QString::fromStdString("Osobné údaje"), this);
    personalDetails->setFixedSize(INFO_PANEL_WIDTH - TITLE_WIDTH, TITLE_HEIGHT / 2);
    personalDetails->setStyleSheet("* {font: bold italic \"Times New Roman\"; qproperty-alignment: AlignCenter; font-size: 13pt;background-color: rgba(0,0,0,0);}");

    hideButton = new QPushButton(this);
    hideButton->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    hideButton->setStyleSheet(
                "* {font-size: 13pt; color: black; background-color: rgba(0,255,0,180); image: url(../imgs/return_mirrored_transparent.png);} \
                *::hover {border: 1.5px solid black; color: white; background-color: rgba(0,155,0,220);}");
    QObject::connect(hideButton, SIGNAL(clicked()), this, SLOT(openIcons()));

    personalData = new PersonalData(mainPanel);
    QObject::connect(this, SIGNAL(updateClientData_s(long)), personalData, SLOT(updateClientData(long)));

    nextMeal = new NextMeal(mainPanel);
    QObject::connect(this, SIGNAL(updateTime_s()), nextMeal, SLOT(updateTime()));

    settings = new SettingsButton(mainPanel);
    QObject::connect(settings, SIGNAL(openSettings_s()), parent, SLOT(openSettings()));

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addWidget(personalDetails, 1, Qt::AlignCenter);
    layoutTop->addWidget(hideButton, 1, Qt::AlignRight);

    layoutMiddle->addLayout(layoutTop);
    layoutMiddle->addWidget(personalData);
    layoutMiddle->addWidget(nextMeal);
    layoutMiddle->addWidget(settings);

    layout = new QVBoxLayout(this);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->addWidget(timePanel);
    layout->addWidget(mainPanel);
    layout->addWidget(supportPanel);

    emit updateClientData_s(id);
}

InfoPanel::~InfoPanel()
{

}

void InfoPanel::sizeChanged(QSize size)
{
    mainPanel->setFixedSize(QSize(INFO_PANEL_WIDTH, size.height() - 2 * TITLE_HEIGHT));
    supportPanel->setFixedSize(QSize(INFO_PANEL_WIDTH, TITLE_HEIGHT));
}

void InfoPanel::updateTime()
{
    timePanel->setText(dateTime.currentDateTime().toString("H:mm:ss dd.MM.yyyy"));
    emit updateTime_s();
}

void InfoPanel::updateClientData(long id)
{
    emit updateClientData_s(id);
}

void InfoPanel::openIcons()
{
    hide();
    emit switchContent_s();
}
