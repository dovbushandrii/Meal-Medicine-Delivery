/**
 * @file orderpreview.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class OrderPreview
 */
#include "orderpreview.h"
#include "mainwindow.h"
#include "popup.h"
#include "../model/daos/OrderDAO.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

OrderPreview::OrderPreview(QWidget *parent, long orderID) : QWidget(parent)
{
    this->orderID = orderID;

    int utc = 1; //TIMEZONE =========================================================

    OrderDAO dao;
    Order* order = dao.readOrder(orderID);
    if(order){
        setFixedSize((2 * TITLE_WIDTH) + (3 * DEFAULT_SPACE) + AMOUNT_WIDTH, (5 * TITLE_HEIGHT) + (5 * DEFAULT_SPACE));

        setAttribute(Qt::WA_StyledBackground, true);
        setStyleSheet(".OrderPreview {background-color: rgba(0,0,0,40); border-radius: 30px;}");

        QObject::connect(this, SIGNAL(deleteOrderItem_s(OrderPreview *)), parent, SLOT(deleteOrderItem(OrderPreview *)));
        QObject::connect(this, SIGNAL(openOrder_s(PendingOrder)), parent, SLOT(openOrder(PendingOrder)));

        // TODO change name according to the orderID
        date = new QLabel(this);
        date->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignLeft; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
        date->setFixedSize(2 * TITLE_WIDTH, TITLE_HEIGHT);
        date->setText(QString::fromStdString(std::to_string(order->getDateAndTime().tm_mday) + "/" +
                                             std::to_string(order->getDateAndTime().tm_mon) + "/" +
                                             std::to_string(order->getDateAndTime().tm_year) + " " +
                                             std::to_string((order->getDateAndTime().tm_hour + utc) % 24) + ":" +
                                             std::to_string(order->getDateAndTime().tm_min) + ":" +
                                             std::to_string(order->getDateAndTime().tm_sec)));

        cancel = new QPushButton("X",this);
        cancel->setFixedSize(TITLE_HEIGHT, TITLE_HEIGHT);
        cancel->setStyleSheet("*{font-size: 13pt; border-radius: 10px; color: red; background-color: rgba(0,0,0,80)} *::hover{background-color: rgba(0,0,0,120)}");
        QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(CreatePopup()));
        //QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(deleteOrderItem()));


        // TODO change name according to the orderID
        // WE DONT HAVE A DESCRIPTION
        description = new QPushButton(this);
        description->setStyleSheet("*{font : 'Arial'; border-radius: 10px; font-size: 13pt; background-color: rgba(0,0,0,40)} *::hover{background-color: rgba(0,0,0,100)}");
        description->setFixedSize(2 * TITLE_WIDTH + AMOUNT_WIDTH + DEFAULT_SPACE, 3 * TITLE_HEIGHT);
        QObject::connect(description, SIGNAL(clicked()), this, SLOT(openOrder()));

        order->updateTotalSum();

        // TODO change name according to the orderID
        totalPrice = new QLabel(this);
        totalPrice->setStyleSheet("* {font : 'Arial'; border-radius: 10px; qproperty-alignment: AlignLeft; font-size: 13pt; color: black; background-color: rgba(0,0,0,40)}");
        totalPrice->setFixedSize(2 * TITLE_WIDTH + AMOUNT_WIDTH + DEFAULT_SPACE, TITLE_HEIGHT);
        totalPrice->setText(QString::fromStdString(DECIMALJESUS(order->getTotalSum())));

        QVBoxLayout *layout = new QVBoxLayout(this);
        QHBoxLayout *layoutTop = new QHBoxLayout();

        layout->setSpacing(DEFAULT_SPACE);
        layout->setMargin(DEFAULT_SPACE);
        layout->setAlignment(Qt::AlignTop);

        layoutTop->setSpacing(DEFAULT_SPACE);
        layoutTop->addWidget(date, Qt::AlignLeft);
        layoutTop->addWidget(cancel, Qt::AlignRight);

        layout->addLayout(layoutTop);

        layout->addWidget(totalPrice);
        layout->addWidget(description);
    }
    else {
        //UNABLE TO LOAD THE ORDER
    }
}

OrderPreview::~OrderPreview()
{

}

void OrderPreview::CreatePopup() {
    Popup *check = new Popup(this, discard);
    check->show();
}

void OrderPreview::deleteOrderItem()
{
    emit deleteOrderItem_s(this);
}

void OrderPreview::openOrder()
{
    this->orderID = orderID;

    OrderDAO dao;
    Order* order = dao.readOrder(orderID);
    if(order){
        PendingOrder pendOrd;
        pendOrd.fillFromOrder(*order);
        emit openOrder_s(pendOrd);
    }
    else {
        //conection troubles
    }
}
