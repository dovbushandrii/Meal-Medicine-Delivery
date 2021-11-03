#ifndef FOODWINDOW_H
#define FOODWINDOW_H

#include "foodtab.h"
//#include "../model/entities/Order.h"

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <vector>
#include <QPushButton>

class FoodWindow : public QWidget
{
    Q_OBJECT
public:
    FoodWindow(QWidget *, long);
    ~FoodWindow();

private:
    long facilityID;
    QWidget *mainWidget;
    QScrollArea *scrollArea;
    QGridLayout *layout;
    QWidget *tabs;
    QPushButton *order;
    QLabel *totalPreview;
    std::vector<FoodTab *> foodTabs;
    void paintEvent(QPaintEvent *);

    int totalOrder;

signals:
    // for changing name of window
    void changeName_s(QString);
//    void makeOrder_s(std::vector<Order>);

public slots:
    void sizeChanged(QSize);
    void updateFacility(long);
    void minusClicked();
    void plusClicked();
    void makeOrder();
};

#endif // FOODWINDOW_H
