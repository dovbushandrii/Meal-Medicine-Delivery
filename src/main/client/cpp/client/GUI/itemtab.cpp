/**
 * @file itemtab.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class ItemTab
 */
#include "itemtab.h"
#include "mainwindow.h"
#include "../model/entities/Meal.h"
#include "../model/entities/Medicine.h"

#include <QStyleOption>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <string>

//TODO: Constructor for Meal and Medicine
ItemTab::ItemTab(QWidget *parent, long facilityID, Meal meal) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->mealID = meal.getId();
    this->type = MEAL;
    this->unitPrice = meal.getPrice();

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    setGraphicsEffect(shadow);

    setFixedSize(TAB_WIDTH, TAB_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".ItemTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s(double)), parent, SLOT(minusClicked(double)));
    QObject::connect(this, SIGNAL(plusClicked_s(double)), parent, SLOT(plusClicked(double)));

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    description = new QLabel(this);
    description->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setFixedWidth(TAB_WIDTH);

    weight = new QLabel(this);
    weight->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    weight->setFixedWidth(TAB_WIDTH);

    price = new QLabel(this);
    price->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setFixedWidth(TAB_WIDTH);

    amount = new QLabel(this);
    amount->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black;}");
    amount->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);

    minus = new QPushButton("-",this);
    minus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    minus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(minus, SIGNAL(clicked()), this, SLOT(minusClicked()));

    plus = new QPushButton("+", this);
    plus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    plus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
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
    layout->addWidget(price);
    layout->addLayout(layoutAmount);

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
    description->setText(QString::fromStdString(meal.getDescription()));
    weight->setText(QString::fromStdString("Hmotnosť: "+std::to_string(meal.getWeight()) + "g"));
    price->setText(QString::fromStdString("Cena za porciu: "+DECIMALJESUS(meal.getPrice()) + " CZK"));
    amount->setText("0");

}

ItemTab::ItemTab(QWidget *parent, long facilityID, Medicine medicine) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->mealID = medicine.getId();
    this->type = MEDICINE;
    this->unitPrice = medicine.getPrice();

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    setGraphicsEffect(shadow);

    setFixedSize(TAB_WIDTH, TAB_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".ItemTab {background-color: rgba(0,0,0,20); border-radius: 30px;}");

    QObject::connect(this, SIGNAL(minusClicked_s(double)), parent, SLOT(minusClicked(double)));
    QObject::connect(this, SIGNAL(plusClicked_s(double)), parent, SLOT(plusClicked(double)));

    picture = new QLabel(this);
    picture->setFixedSize(PIC_WIDTH, PIC_HEIGHT);
    picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    description = new QLabel(this);
    description->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    description->setFixedWidth(TAB_WIDTH);

    weight = new QLabel(this);
    weight->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    weight->setFixedWidth(TAB_WIDTH);

    price = new QLabel(this);
    price->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black; background-color: rgba(0,0,0,40)}");
    price->setFixedWidth(TAB_WIDTH);

    amount = new QLabel(this);
    amount->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignCenter; font-size: 15pt; color: black;}");
    amount->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);

    minus = new QPushButton("-",this);
    minus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    minus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
    QObject::connect(minus, SIGNAL(clicked()), this, SLOT(minusClicked()));

    plus = new QPushButton("+", this);
    plus->setFixedSize(AMOUNT_WIDTH, AMOUNT_HEIGHT);
    plus->setStyleSheet("*{font-size: 13pt; border-radius: 10px; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
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
    layout->addWidget(price);
    layout->addLayout(layoutAmount);


    //SET BYTEARRAY
    std::string image = medicine.getImage();
    QByteArray* loadImage = new QByteArray(image.c_str(),image.length());

    // check for available medicine picture from facility
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
    description->setText(QString::fromStdString(medicine.getDescription()));
    unitPrice = medicine.getPrice();
    price->setText(QString::fromStdString("Cena za porciu: "+DECIMALJESUS(medicine.getPrice()) + " CZK"));
    amount->setText("0");
}

ItemTab::~ItemTab()
{

}

std::pair<long, int> ItemTab::getAmount()
{
    return {mealID, amount->text().toInt()};
}

void ItemTab::setAmount(int newAmount) {
     amount->setText(QString::fromStdString(std::to_string(newAmount)));
}

void ItemTab::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ItemTab::minusClicked()
{
    if (amount->text().toInt() != 0)
        emit minusClicked_s(-(unitPrice));

    amount->setText(QString::fromStdString(std::to_string(std::max(0, amount->text().toInt() - 1))));
}

void ItemTab::plusClicked()
{
    amount->setText(QString::fromStdString(std::to_string(std::stoi(amount->text().toStdString()) + 1)));
    emit plusClicked_s(unitPrice);
}
