#include "infopanel.h"

#include <QDebug>

InfoPanel::InfoPanel(MainWindow *parent, long id) : QWidget(parent)
{
    timePanel = new QLabel(dateTime.currentDateTime().toString("H:mm:ss dd.MM.yyyy"), this);
    mainPanel = new QWidget(parent);
    supportPanel = new QLabel("Telefónne číslo na podporu\nxxxx xxx xxx", this);
    timePanel->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 15pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");
    mainPanel->setStyleSheet(".QWidget {border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");
    supportPanel->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 12pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");

    layoutMiddle = new QVBoxLayout(mainPanel);
    layoutMiddle->setSpacing(0);

    personalData = new PersonalData(mainPanel);
    QObject::connect(this, SIGNAL(updateClientData_s(long)), personalData, SLOT(updateClientData(long)));

    nextMeal = new NextMeal(mainPanel);
    QObject::connect(this, SIGNAL(updateTime_s()), nextMeal, SLOT(updateTime()));


    layoutMiddle->addWidget(personalData);
    layoutMiddle->addWidget(nextMeal);

    layout = new QVBoxLayout(this);

    layout->setSizeConstraint(QLayout::SetFixedSize);
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
    timePanel->setFixedSize(QSize(INFO_PANEL_WIDTH, TITLE_HEIGHT));
    mainPanel->setFixedSize(QSize(INFO_PANEL_WIDTH, size.height() - 4 * TITLE_HEIGHT));
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
