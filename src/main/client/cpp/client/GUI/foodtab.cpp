#include "foodtab.h"
#include "mainwindow.h"
#include "../model/daos/MealDAO.h"
#include "../model/entities/Meal.h"

#include <QStyleOption>
#include <QPainter>

FoodTab::FoodTab(QWidget *parent, long facilityID, long mealID) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->mealID = mealID;

    setFixedSize(TAB_WIDTH, TAB_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".FoodTab {background-color: rgba(0,0,0,30); border-radius: 10px;}");
    raise();


    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    description = new QLabel(this);
    description->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,0)}");
    description->setFixedWidth(TAB_WIDTH);

    weight = new QLabel(this);
    weight->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,0)}");
    weight->setFixedWidth(TAB_WIDTH);

    price = new QLabel(this);
    price->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black; background-color: rgba(0,0,0,0)}");
    price->setFixedWidth(TAB_WIDTH);

    amount = new QLabel(this);
    amount->setStyleSheet("* {qproperty-alignment: AlignCenter; font-size: 9.2pt; color: black;}");
    amount->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);

    minus = new QPushButton("-",this);
    minus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    minus->setStyleSheet("*{background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(minus, SIGNAL(clicked()), this, SLOT(minusClicked()));

    plus = new QPushButton("+", this);
    plus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    plus->setStyleSheet("*{background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(plus, SIGNAL(clicked()), this, SLOT(plusClicked()));

    layoutAmount = new QHBoxLayout();
    layoutAmount->setSpacing(0);
    layoutAmount->setAlignment(Qt::AlignCenter);
    layoutAmount->addWidget(minus);
    layoutAmount->addWidget(amount);
    layoutAmount->addWidget(plus);

    layoutPicture = new QHBoxLayout();
    layoutPicture->addWidget(picture);

    layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    layout->addLayout(layoutPicture);
    layout->addWidget(description);
    layout->addWidget(weight);
    layout->addWidget(price);
    layout->addLayout(layoutAmount);

    updateMeal();
}

FoodTab::~FoodTab()
{

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
    amount->setText(QString::fromStdString(std::to_string(std::max(0, std::stoi(amount->text().toStdString()) - 1))));
}

void FoodTab::plusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::min(MAX_AMOUNT, std::stoi(amount->text().toStdString()) + 1))));
}

void FoodTab::updateMeal()
{
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

void FoodTab::updateFacility(long newFacilityID, long newMealID)
{
    facilityID = newFacilityID;
    mealID = newMealID;
}
