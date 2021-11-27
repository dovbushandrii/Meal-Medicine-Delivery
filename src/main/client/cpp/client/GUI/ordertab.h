/**
 * @file ordertab.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderTab, which displays info about item being ordered
 */
#ifndef ORDERTAB_H
#define ORDERTAB_H

#include "mainwindow.h"

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
    OrderTab(QWidget *, long, long, ItemType, int);
    ~OrderTab();

private:
    long facilityID;
    long itemID;

    ItemType type;

    QLabel *picture;
    QLabel *description;
    QLabel *price;
    QLabel *totalPrice;
    QPushButton *cancel;

    QLabel *amount;
    QPushButton *minus;
    QPushButton *plus;

    void paintEvent(QPaintEvent *);

signals:
    void minusClicked_s();
    void plusClicked_s();
    void deleteOrderItem_s(OrderTab *);

public slots:
    void sizeChanged(QSize);
    void CreatePopup();

private slots:
    void minusClicked();
    void plusClicked();
    void deleteOrderItem();

};

#endif // ORDERTAB_H
