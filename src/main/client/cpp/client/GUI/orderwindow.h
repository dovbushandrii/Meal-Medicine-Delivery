/**
 * @file orderwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderWindow, which displays items to-be-ordered
 */
#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include "ordertab.h"
#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

enum OrderWindowType {ORDER, EDIT};

class OrderWindow : public QWidget
{
    Q_OBJECT
public:
    OrderWindow(QWidget *, long, long, ItemType, OrderWindowType = ORDER);
    ~OrderWindow();

private:
    OrderWindowType type;
    ItemType itemType;
    long facilityID;
    long orderID;

    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QVBoxLayout *layout;
    QWidget *tabs;
    QPushButton *order;
    QLabel *totalPrice;
    std::vector<OrderTab *> orderTabs;  // vector of displayed items in order

    // custom override for transparency
    void paintEvent(QPaintEvent *);

    // for rearrangment of widgets in scroll area
    void updateAll();

signals:
    // for orderTab
    void sizeChanged_s(QSize);
    // for changing name of window
    void changeName_s(QString);
    void confirmOrder_s(long);

public slots:
    void sizeChanged(QSize);
    void updateFacility(long);
    void updateOrder(long);
    void minusClicked();
    void plusClicked();
    void deleteOrderItem(OrderTab *);
    void confirmOrder();
};

#endif // ORDERWINDOW_H
