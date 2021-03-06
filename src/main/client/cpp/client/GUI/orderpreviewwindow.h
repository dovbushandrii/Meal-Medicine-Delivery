/**
 * @file orderpreviewwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderPreviewWindow, which shows all ordered items from certain order
 */
#ifndef ORDERPREVIEWWINDOW_H
#define ORDERPREVIEWWINDOW_H

#include "orderpreview.h"
#include "../model/entities/PendingOrder.h"

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <vector>
#include <QGridLayout>

class OrderPreviewWindow : public QWidget
{
    Q_OBJECT
public:
    OrderPreviewWindow(QWidget *, long);
    ~OrderPreviewWindow();

private:
    long facilityID;
    QGridLayout *layout;

    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QWidget *tabs;

    std::vector<OrderPreview *> orders; // vector of all current orders

    // custom override for transparency
    void paintEvent(QPaintEvent *);

    // for rearrangment of currently displayed widgets
    void updateAll();
    void loadOrders();

signals:
    // for changing name of window
    void changeName_s(QString);
    // for opening certain order
    void openOrder_s(PendingOrder);

    void updateOrders_s(std::vector<Order>*);

public slots:
    void sizeChanged(QSize);
    void openOrder(PendingOrder);
    void deleteOrderItem(OrderPreview *);   // to delete order from orders
    void updateOrders(std::vector<Order>*);
};

#endif // ORDERPREVIEWWINDOW_H
