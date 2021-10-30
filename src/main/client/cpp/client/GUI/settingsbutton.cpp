#include "settingsbutton.h"
#include "mainwindow.h"
#include "infopanel.h"

#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>

SettingsButton::SettingsButton(QWidget *parent) : QWidget(parent)
{
    setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT);
    setStyleSheet(
                    "* {background-color: rgba(0,0,0,0);} \
                    *::hover {background-color: rgba(20,20,20,100);}");

    label = new QPushButton("Nastavenia", this);
    label->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT);
    label->setStyleSheet("* {font: bold italic \"Times New Roman\"; font-size: 11pt; color: white; background-color: rgba(0,0,0,0);}");
    QObject::connect(label, SIGNAL(clicked()), this, SLOT(openSettings()));
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
}

SettingsButton::~SettingsButton()
{

}

void SettingsButton::openSettings()
{
    emit openSettings_s();
}

void SettingsButton::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

