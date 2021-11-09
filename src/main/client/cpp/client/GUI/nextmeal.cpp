/**
 * @file nextmeal.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class NextMeal
 */
#include "nextmeal.h"
#include "mainwindow.h"
#include "infopanel.h"
#include "../model/daos/MealDAO.h"

#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

NextMeal::NextMeal(QWidget *parent) : QWidget(parent)
{
    pressed = false;

    // sum of elements heights
    setFixedSize(INFO_PANEL_WIDTH, 2 * TITLE_HEIGHT);
    setStyleSheet(
                    "* {background-color: rgba(0,0,0,0);} \
                    *::hover {background-color: rgba(20,20,20,100);}");

    title = new QLabel("Prepokladaný čas príchodu objednávky:", this);
    title->setStyleSheet("* {font: bold italic underline \"Times New Roman\"; font-size: 11pt; color: black; qproperty-alignment: AlignLeft; background-color: rgba(0,0,0,0);}");
    title->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT / 2);

    time = new QLabel(this);
    time->setStyleSheet("* {font-size: 11pt; color: black; qproperty-alignment: AlignLeft; background-color: rgba(0,0,0,0);}");
    time->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT / 2);

    details = new QLabel("rozkliknite pre viac detailov", this);
    details->setStyleSheet("* {font-size: 11pt; color: black; qproperty-alignment: AlignLeft; background-color: rgba(0,0,0,0);}");
    details->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT / 2);

    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->addWidget(title);
    layout->addWidget(time);
    layout->addWidget(details);

    updateTime();
}

NextMeal::~NextMeal()
{

}
void NextMeal::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
        pressed = true;
}

void NextMeal::mouseMoveEvent(QMouseEvent *event)
{
    (void) event;
    pressed = false;
}

void NextMeal::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        if (pressed)
            emit showOrderDetails();
    }
}

void NextMeal::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void NextMeal::updateNextMeal()
{
    MealDAO mealDAO;
    (void) mealDAO;
    // TO DO
}

void NextMeal::updateTime()
{
    time->setText(QString::fromStdString("NaN"));
    // TO DO update time of expected arrival
}
