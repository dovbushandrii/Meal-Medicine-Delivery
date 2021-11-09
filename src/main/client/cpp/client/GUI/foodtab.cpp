/**
 * @file foodtab.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class FoodTab
 */
#include "foodtab.h"
#include "mainwindow.h"
#include "../model/daos/MealDAO.h"
#include "../model/entities/Meal.h"

#include <QStyleOption>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

FoodTab::FoodTab(QWidget *parent, long facilityID, long mealID) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->mealID = mealID;

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    setGraphicsEffect(shadow);

    setFixedSize(TAB_WIDTH, TAB_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".FoodTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s()), parent, SLOT(minusClicked()));
    QObject::connect(this, SIGNAL(plusClicked_s()), parent, SLOT(plusClicked()));

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    description = new QLabel(this);
    description->setStyleSheet("* {border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setFixedWidth(TAB_WIDTH);

    weight = new QLabel(this);
    weight->setStyleSheet("* {border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,40)}");
    weight->setFixedWidth(TAB_WIDTH);

    price = new QLabel(this);
    price->setStyleSheet("* {border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setFixedWidth(TAB_WIDTH);

    amount = new QLabel(this);
    amount->setStyleSheet("* {border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black;}");
    amount->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);

    minus = new QPushButton("-",this);
    minus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    minus->setStyleSheet("*{border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(minus, SIGNAL(clicked()), this, SLOT(minusClicked()));

    plus = new QPushButton("+", this);
    plus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    plus->setStyleSheet("*{border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(plus, SIGNAL(clicked()), this, SLOT(plusClicked()));

    layoutAmount = new QHBoxLayout();
    layoutAmount->setSpacing(0);
    layoutAmount->setAlignment(Qt::AlignCenter);
    layoutAmount->addWidget(minus);
    layoutAmount->addWidget(amount);
    layoutAmount->addWidget(plus);

    layoutPicture = new QHBoxLayout();
    layoutPicture->setContentsMargins(0, DEFAULT_SPACE, 0, 0);
    layoutPicture->addWidget(picture);

    layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    layout->addLayout(layoutPicture);
    layout->addWidget(description);
    layout->addWidget(weight);
    layout->addWidget(price);
    layout->addLayout(layoutAmount);

    //    MealDAO mealDAO;
    //    Meal meal = mealDAO.readMeal(mealID);
    Meal meal;

    // check for available food picture from facility
    // TODO
    picture->setStyleSheet("* {image: url(../imgs/food_default.png);}");
    description->setText(QString::fromStdString(meal.getDescription()));
    weight->setText(QString::fromStdString("Hmotnosť: "+std::to_string(meal.getWeight())));
    price->setText(QString::fromStdString("Cena za porciu: "+std::to_string(meal.getPrice())));
    amount->setText("0");
}

FoodTab::~FoodTab()
{

}

std::pair<long, int> FoodTab::getAmount()
{
    return {mealID, amount->text().toInt()};
}

void FoodTab::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FoodTab::minusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::max(0, amount->text().toInt() - 1))));
    emit minusClicked_s();
}

void FoodTab::plusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::min(MAX_AMOUNT, std::stoi(amount->text().toStdString()) + 1))));
    emit plusClicked_s();
}
