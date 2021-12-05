/**
 * @file ordertab.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderTab, which displays info about item being ordered
 */
#ifndef ORDERTAB_H
#define ORDERTAB_H

#include "mainwindow.h"
#include "../model/entities/Meal.h"
#include "../model/entities/Medicine.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class OrderTab : public QWidget
{
    Q_OBJECT
public:
    OrderTab(QWidget *, Medicine, int*);
    OrderTab(QWidget *, Meal, int*);
    ~OrderTab();

    double getPrice();

    long itemID;
    ItemType type;
    int* amountOf;

private:
    long facilityID;


    QLabel *picture;
    QLabel *description;
    QLabel *price;
    QLabel *totalPrice;
    QPushButton *cancel;

    QLabel *amount;
    QPushButton *minus;
    QPushButton *plus;

    double unitPrice;
    double totalSum;

    void paintEvent(QPaintEvent *);

signals:
    void minusClicked_s(double);
    void plusClicked_s(double);
    void deleteOrderItem_s(OrderTab *);

public slots:
    void sizeChanged(QSize);
    void CreatePopup();

private slots:
    void minusClicked();
    void plusClicked();
    void deleteOrderItem(); // to remove item from order

};

#endif // ORDERTAB_H
