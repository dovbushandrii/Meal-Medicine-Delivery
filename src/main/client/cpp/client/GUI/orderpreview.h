/**
 * @file orderpreview.h
 * @author Rastislav Budinsky
 * @brief This file contains class OrderPreview, which shows one ordered item
 */
#ifndef ORDERPREVIEW_H
#define ORDERPREVIEW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class OrderPreview : public QWidget
{
    Q_OBJECT
public:
    OrderPreview(QWidget *, long);
    ~OrderPreview();

private:
    long orderID;

    QLabel *date;
    QPushButton *cancel;
    QLabel *totalPrice;
    QPushButton *description;

signals:
    void deleteOrderItem_s(OrderPreview *);
    void openOrder_s(long);

private slots:
    void deleteOrderItem();
    void openOrder();
    void CreatePopup();
};

#endif // ORDERPREVIEW_H
