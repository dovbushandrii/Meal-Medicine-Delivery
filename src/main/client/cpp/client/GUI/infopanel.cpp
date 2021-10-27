#include "infopanel.h"

InfoPanel::InfoPanel(MainWindow *parent) : QWidget(parent)
{
    timePanel = new QLabel(dateTime.currentDateTime().toString("H:mm:ss dd.MM.yyyy"), this);
    mainPanel = new QWidget(parent);
    supportPanel = new QLabel("Telefónne číslo na podporu\nxxxx xxx xxx", this);
    timePanel->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 15pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");
    mainPanel->setStyleSheet("* {border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");
    supportPanel->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 12pt; color: black; border: 2px solid black; border-radius: 10px; background-color: rgba(20,20,20,120);}");

    layout = new QVBoxLayout(this);

    layout->addWidget(timePanel);
    layout->addWidget(mainPanel);
    layout->addWidget(supportPanel);
}

void InfoPanel::sizeChanged(QSize size)
{
    timePanel->setFixedSize(QSize(5 * TITLE_WIDTH, TITLE_HEIGHT));
    mainPanel->setFixedSize(QSize(5 * TITLE_WIDTH, size.height() - 4 * TITLE_HEIGHT));
    supportPanel->setFixedSize(QSize(5 * TITLE_WIDTH, TITLE_HEIGHT));
}

InfoPanel::~InfoPanel()
{

}

void InfoPanel::updateTime()
{
    timePanel->setText(dateTime.currentDateTime().toString("H:mm:ss dd.MM.yyyy"));
}
