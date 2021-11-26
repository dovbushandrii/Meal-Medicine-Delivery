/**
 * @file ordertab.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class OrderTab
 */
#include "ordertab.h"

#include "../model/daos/MealDAO.h"
#include "../model/daos/MedicineDAO.h"
#include "../model/entities/Meal.h"
#include "../model/entities/Medicine.h"

#include <QStyleOption>
#include <QPainter>

OrderTab::OrderTab(QWidget *parent, long facilityID, long itemID, ItemType type, int initialAmount) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->itemID = itemID;
    this->type = type;

    // TODO
//    MealDAO mealDAO;
//    MedicineDAO medicineDAO;
//    Meal meal = mealDAO.readMeal(itemID);
//    Medicine medicine = medicineDAO.readMedicine(itemID);

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".OrderTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s()), parent, SLOT(minusClicked()));
    QObject::connect(this, SIGNAL(plusClicked_s()), parent, SLOT(plusClicked()));
    QObject::connect(this, SIGNAL(deleteOrderItem_s(OrderTab *)), parent, SLOT(deleteOrderItem(OrderTab *)));

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (type == MEAL)
        picture->setStyleSheet("* {image: url(../imgs/food_default.png);}");
    else
        picture->setStyleSheet("* {image: url(../imgs/medicine_default.png);}");

    description = new QLabel(this);
    description->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setMinimumWidth(2 * TITLE_WIDTH);

    price = new QLabel(this);
    price->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setMinimumWidth(2 * TITLE_WIDTH);

    totalPrice = new QLabel(this);
    totalPrice->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    totalPrice->setMinimumWidth(2 * TITLE_WIDTH);

    amount = new QLabel(QString::fromStdString(std::to_string(initialAmount)), this);
    amount->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black;}");
    amount->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);

    minus = new QPushButton("-",this);
    minus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    minus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(minus, SIGNAL(clicked()), this, SLOT(minusClicked()));

    plus = new QPushButton("+", this);
    plus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    plus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(plus, SIGNAL(clicked()), this, SLOT(plusClicked()));

    cancel = new QPushButton("X",this);
    cancel->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    cancel->setStyleSheet("*{font-size: 13pt; border-radius: 10px; color: red; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(deleteOrderItem()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *layoutRight = new QVBoxLayout();
    QHBoxLayout *layoutRightTop = new QHBoxLayout();
    QVBoxLayout *layoutAmount = new QVBoxLayout();

    layout->setSpacing(DEFAULT_SPACE);
    layout->setMargin(DEFAULT_SPACE);
    layout->setAlignment(Qt::AlignCenter);

    layoutAmount->setSpacing(0);
    layoutAmount->setAlignment(Qt::AlignCenter);


    layoutAmount->addWidget(plus);
    layoutAmount->addWidget(amount);
    layoutAmount->addWidget(minus);
    layoutRightTop->addWidget(price);
    layoutRightTop->addWidget(cancel, Qt::AlignLeft);
    layoutRight->addLayout(layoutRightTop);
    layoutRight->addWidget(totalPrice);
    layout->addWidget(picture);
    layout->addWidget(description);
    layout->addLayout(layoutAmount);
    layout->addLayout(layoutRight);
}

OrderTab::~OrderTab()
{

}

void OrderTab::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void OrderTab::sizeChanged(QSize size)
{
    setFixedSize(size.width(), size.height());
}

void OrderTab::minusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::max(0, amount->text().toInt() - 1))));
    emit minusClicked_s();
}

void OrderTab::plusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::min(MAX_AMOUNT, std::stoi(amount->text().toStdString()) + 1))));
    emit plusClicked_s();
}

void OrderTab::deleteOrderItem()
{
    emit deleteOrderItem_s(this);
}
