#include "menu.h"

Menu::Menu(QWidget *parent, long clientID) : QWidget(parent)
{
    this->clientID = clientID;

    QObject::connect(this, SIGNAL(openSettings_s()), parent, SLOT(openSettings()));
    QObject::connect(this, SIGNAL(changeSize_s()), parent, SLOT(changeSize()));

    infoPanel = new InfoPanel(this, clientID);
    icons = new InfoPanelIcons(this);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(icons);

    infoPanel->hide();
    showingIcons = true;
}

Menu::~Menu()
{

}

bool Menu::isInfoPanel()
{
    return !showingIcons;
}

void Menu::updateTime()
{
    emit updateTime_s();
}

void Menu::sizeChanged(QSize size)
{
    emit sizeChanged_s(QSize(INFO_PANEL_WIDTH, size.height() - TITLE_HEIGHT));
}

void Menu::updateClientData(long newID)
{
    emit updateClientData_s(newID);
}

void Menu::openSettings()
{
    emit openSettings_s();
}

void Menu::switchContent()
{
    if (showingIcons)
    {
        infoPanel->show();
        layout->replaceWidget(icons, infoPanel);
    }
    else
    {
        icons->show();
        layout->replaceWidget(infoPanel, icons);
    }

    showingIcons = !showingIcons;

    emit changeSize_s();
}

