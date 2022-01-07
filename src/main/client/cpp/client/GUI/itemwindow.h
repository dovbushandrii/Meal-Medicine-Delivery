/**
 * @file itemwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class ItemWindow, one widget displaying multiple ItemTab items
 */
#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include "itemtab.h"
#include "../model/entities/PendingOrder.h"
#include "../model/entities/Facility.h"

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <vector>
#include <QPushButton>

class ItemWindow : public QWidget
{
    Q_OBJECT
public:
    ItemWindow(QWidget *, long, ItemType, PendingOrder*);
    ~ItemWindow();

private:
    long facilityID;
    ItemType type;
    PendingOrder* pendingOrder;

    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QGridLayout *layout;
    QWidget *tabs;
    QPushButton *order;
    QLabel *totalPreview;
    std::vector<ItemTab *> foodTabs;    // vector of items currently displayed

    // custom override for transparency
    void paintEvent(QPaintEvent *);

    void updateListOfItems();

    void updatePendingOrder();

    int totalOrder;
    double totalPrice;

signals:
    // for changing name of window
    void changeName_s(QString);
    void makeOrder_s(long, ItemType);
    void updateItems_s(Facility*);

public slots:
    void sizeChanged(QSize);
    void updateFacility(long);
    void updateCurrentFacility();
    void minusClicked(double);
    void plusClicked(double);
    void makeOrder();
    void updateItems(Facility*);
};

#endif // ITEMWINDOW_H
