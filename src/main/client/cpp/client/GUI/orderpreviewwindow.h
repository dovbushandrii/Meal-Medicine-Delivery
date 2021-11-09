/**
 * @file orderpreviewwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderPreviewWindow, which shows all ordered items from certain order
 */
#ifndef ORDERPREVIEWWINDOW_H
#define ORDERPREVIEWWINDOW_H

#include "orderpreview.h"

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

    std::vector<OrderPreview *> orders;
    void paintEvent(QPaintEvent *);
    void updateAll();

signals:
    // for changing name of window
    void changeName_s(QString);
    // for opening certain order
    void openOrder_s(long);

public slots:
    void sizeChanged(QSize);
    void openOrder(long);
    void deleteOrderItem(OrderPreview *);
};

#endif // ORDERPREVIEWWINDOW_H
