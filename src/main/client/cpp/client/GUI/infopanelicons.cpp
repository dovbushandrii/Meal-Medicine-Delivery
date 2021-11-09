#include "infopanelicons.h"
#include "mainwindow.h"

#include <QVBoxLayout>

InfoPanelIcons::InfoPanelIcons(QWidget *parent) : QWidget(parent)
{
    QObject::connect(this, SIGNAL(switchContent_s()), parent, SLOT(switchContent()));
    QObject::connect(this, SIGNAL(openSettings_s()), parent, SLOT(openSettings()));

    profile = new QPushButton(this);
    profile->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
    profile->setStyleSheet(
                "* {background-color: rgba(0,0,0,0); image: url(../imgs/user_profile_transparent.png);} \
                *::hover {border: 1.5px solid black; background-color: rgba(0,0,0,100);}");
    QObject::connect(profile, SIGNAL(clicked()), this, SLOT(openInfoPanel()));

    settings = new QPushButton(this);
    settings->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
    settings->setStyleSheet(
                "* {background-color: rgba(0,0,0,0); image: url(../imgs/settings_transparent.png);} \
                *::hover {border: 1.5px solid black; background-color: rgba(0,0,0,100);}");
    QObject::connect(settings, SIGNAL(clicked()), this, SLOT(openSettings()));

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setSpacing(DEFAULT_SPACE);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(profile);
    layout->addWidget(settings);
}

InfoPanelIcons::~InfoPanelIcons()
{

}

void InfoPanelIcons::openSettings()
{
    emit openSettings_s();
}

void InfoPanelIcons::openInfoPanel()
{
    hide();
    emit switchContent_s();
}

