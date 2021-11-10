/**
 * @file itemwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class ItemWindow, one widget displaying multiple ItemTab items
 */
#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include "itemtab.h"
//#include "../model/entities/Order.h"

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
    ItemWindow(QWidget *, long, ItemType);
    ~ItemWindow();

private:
    long facilityID;
    ItemType type;

    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QGridLayout *layout;
    QWidget *tabs;
    QPushButton *order;
    QLabel *totalPreview;
    std::vector<ItemTab *> foodTabs;
    void paintEvent(QPaintEvent *);

    int totalOrder;

signals:
    // for changing name of window
    void changeName_s(QString);
    void makeOrder_s(long);

public slots:
    void sizeChanged(QSize);
    void updateFacility(long);
    void minusClicked();
    void plusClicked();
    void makeOrder();
};

#endif // ITEMWINDOW_H
