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
    OrderWindow(QWidget *, PendingOrder*, OrderWindowType = ORDER);
    ~OrderWindow();

private:
    OrderWindowType type;
    PendingOrder* pendingOrder;


    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QVBoxLayout *layout;
    QWidget *tabs;
    QPushButton *order;
    QLabel *totalPrice;
    std::vector<OrderTab *> orderTabs;  // vector of displayed items in order

    double sumPrice;

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
    void orderChanged_s();

public slots:
    void sizeChanged(QSize);
    // propagating the change in price
    void minusClicked(double);
    void plusClicked(double);
    void deleteOrderItem(OrderTab *);
    void confirmOrder();
};

#endif // ORDERWINDOW_H
