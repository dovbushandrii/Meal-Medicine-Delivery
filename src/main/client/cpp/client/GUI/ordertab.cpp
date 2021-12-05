/**
 * @file ordertab.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class OrderTab
 */
#include "ordertab.h"
#include "popup.h"

#include "../model/daos/MealDAO.h"
#include "../model/daos/MedicineDAO.h"
#include "../model/entities/Meal.h"
#include "../model/entities/Medicine.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>

OrderTab::OrderTab(QWidget *parent, Medicine medicine, int* initialAmount) : QWidget(parent)
{
    amountOf = initialAmount;
    itemID = medicine.getId();
    type = MEDICINE;

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".OrderTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s(double)), parent, SLOT(minusClicked(double)));
    QObject::connect(this, SIGNAL(plusClicked_s(double)), parent, SLOT(plusClicked(double)));
    QObject::connect(this, SIGNAL(deleteOrderItem_s(OrderTab *)), parent, SLOT(deleteOrderItem(OrderTab *)));

    //TODO UNDERSTAND WHAT IS GOING ON

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);

    std::string image = medicine.getImage();
    QByteArray* loadImage = new QByteArray(image.c_str(),image.length());

    // check for available food picture from facility
    if(!loadImage->isEmpty()){
        QImage img;
        img.loadFromData(QByteArray::fromBase64(*loadImage));
        picture->setPixmap(QPixmap::fromImage(img));
        picture->setScaledContents( true );

        picture->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        //picture.show()?
    }
    else{
         picture->setStyleSheet("* {image: url(../imgs/medicine_default.png);}");
    }


    // TODO change accordingly to the ID
    description = new QLabel(this);
    description->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setMinimumWidth(2 * TITLE_WIDTH);
    description->setText(QString::fromStdString(medicine.getDescription()));

    // TODO change accordingly to the ID
    price = new QLabel(this);
    price->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setMinimumWidth(2 * TITLE_WIDTH);
    price->setText(QString::fromStdString(std::to_string(medicine.getPrice())));

    // TODO change accordingly to the ID
    totalPrice = new QLabel(this);
    totalPrice->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    totalPrice->setMinimumWidth(2 * TITLE_WIDTH);

    this->unitPrice = medicine.getPrice();
    totalPrice->setText(QString::fromStdString(std::to_string(unitPrice * (*initialAmount))));

    // TODO change accordingly to the ID
    amount = new QLabel(QString::fromStdString(std::to_string(*initialAmount)), this);
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
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(CreatePopup()));
    //QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(deleteOrderItem()));

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

OrderTab::OrderTab(QWidget *parent, Meal meal, int* initialAmount) : QWidget(parent)
{
    amountOf = initialAmount;
    itemID = meal.getId();
    type = MEAL;

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".OrderTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s()), parent, SLOT(minusClicked()));
    QObject::connect(this, SIGNAL(plusClicked_s()), parent, SLOT(plusClicked()));
    QObject::connect(this, SIGNAL(deleteOrderItem_s(OrderTab *)), parent, SLOT(deleteOrderItem(OrderTab *)));

    //TODO UNDERSTAND WHAT IS GOING ON

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    std::string image = meal.getImage();
    QByteArray* loadImage = new QByteArray(image.c_str(),image.length());

    // check for available food picture from facility
    if(!loadImage->isEmpty()){
        QImage img;
        img.loadFromData(QByteArray::fromBase64(*loadImage));
        picture->setPixmap(QPixmap::fromImage(img));
        picture->setScaledContents( true );

        picture->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        //picture.show()?
    }
    else{
        picture->setStyleSheet("* {image: url(../imgs/food_default.png);}");
    }

    // TODO change accordingly to the ID
    description = new QLabel(this);
    description->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setMinimumWidth(2 * TITLE_WIDTH);
    description->setText(QString::fromStdString(meal.getDescription()));

    // TODO change accordingly to the ID
    price = new QLabel(this);
    price->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setMinimumWidth(2 * TITLE_WIDTH);
    price->setText(QString::fromStdString(std::to_string(meal.getPrice())));

    // TODO change accordingly to the ID
    totalPrice = new QLabel(this);
    totalPrice->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
    totalPrice->setMinimumWidth(2 * TITLE_WIDTH);
    totalPrice->setText(QString::fromStdString(std::to_string(meal.getPrice() * (*initialAmount))));

    // TODO change accordingly to the ID
    amount = new QLabel(QString::fromStdString(std::to_string(*initialAmount)), this);
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
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(CreatePopup()));
    //QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(deleteOrderItem()));

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

void OrderTab::CreatePopup() {
    Popup *check = new Popup(this, discard);
    check->show();
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
    (*amountOf)--;
    emit minusClicked_s(-unitPrice);
}

void OrderTab::plusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::min(MAX_AMOUNT, std::stoi(amount->text().toStdString()) + 1))));
    (*amountOf)++;
    emit plusClicked_s(unitPrice);
}

void OrderTab::deleteOrderItem()
{
    emit deleteOrderItem_s(this);
}
