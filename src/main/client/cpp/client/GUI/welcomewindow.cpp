/**
 * @file welcomewindow.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class WelcomeWindow
 */
#include "welcomewindow.h"
#include "mainwindow.h"
#include "infopanel.h"

#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>

WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent)
{
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    setStyleSheet(".WelcomeWindow {background-color: transparent}");

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet(".QWidget{border-radius: 30px; background-color: rgba(0, 0, 0, 40)}");
    mainWidget->setFixedSize(width(), height());

    foodWindow = new QPushButton("Objednanie stravy", mainWidget);
    medicineWindow = new QPushButton("Objednanie liekov", mainWidget);
    ordersWindow = new QPushButton("Prehľad objednávok", mainWidget);
    medicineSchedule = new QPushButton("Rozvrh liekov", mainWidget);

    foodWindow->setStyleSheet("*{font-size: 30px; border: 2px solid black; border-radius: 20px; background-color: rgba(0,0,0,80)} *::hover{border: 5px solid black; background-color: rgba(0,0,0,120)}");
    medicineWindow->setStyleSheet("*{font-size: 30px; border: 2px solid black; border-radius: 20px; background-color: rgba(0,0,0,80)} *::hover{border: 5px solid black; background-color: rgba(0,0,0,120)}");
    ordersWindow->setStyleSheet("*{font-size: 30px; border: 2px solid black; border-radius: 20px; background-color: rgba(0,0,0,80)} *::hover{border: 5px solid black; background-color: rgba(0,0,0,120)}");
    medicineSchedule->setStyleSheet("*{font-size: 30px; border: 2px solid black; border-radius: 20px; background-color: rgba(0,0,0,80)} *::hover{border: 5px solid black; background-color: rgba(0,0,0,120)}");

    QObject::connect(foodWindow, SIGNAL(clicked()), parent, SLOT(orderFood()));
    QObject::connect(medicineWindow, SIGNAL(clicked()), parent, SLOT(orderMedicine()));
    QObject::connect(ordersWindow, SIGNAL(clicked()), parent, SLOT(previewOrders()));
    QObject::connect(medicineSchedule, SIGNAL(clicked()), parent, SLOT(previewMedicines()));

    QGridLayout *layout = new QGridLayout(mainWidget);
    layout->setSpacing(DEFAULT_SPACE);
    layout->setMargin(DEFAULT_SPACE);
    layout->setAlignment(Qt::AlignCenter);

    layout->addWidget(foodWindow, 0, 0);
    layout->addWidget(medicineWindow, 0, 1);
    layout->addWidget(ordersWindow, 1, 0);
    layout->addWidget(medicineSchedule, 1, 1);
}

WelcomeWindow::~WelcomeWindow()
{

}

void WelcomeWindow::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void WelcomeWindow::sizeChanged(QSize size)
{
    emit changeName_s("Domov");

    setFixedSize(size);
    mainWidget->setFixedSize(size);
    size.setWidth(size.width() - (3 * DEFAULT_SPACE));
    size.setHeight(size.height() - (3 * DEFAULT_SPACE));
    foodWindow->setFixedSize(size.width() / 2, size.height() / 2);
    medicineWindow->setFixedSize(size.width() / 2, size.height() / 2);
    ordersWindow->setFixedSize(size.width() / 2, size.height() / 2);
    medicineSchedule->setFixedSize(size.width() / 2, size.height() / 2);
}
