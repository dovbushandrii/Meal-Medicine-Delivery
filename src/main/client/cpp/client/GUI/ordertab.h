#ifndef ORDERTAB_H
#define ORDERTAB_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#define AMOUNT_ORDER_WIDTH 40
#define AMOUNT_ORDER_HEIGHT AMOUNT_ORDER_WIDTH

enum OrderTabType {MEAL, MEDICINE};

class OrderTab : public QWidget
{
    Q_OBJECT
public:
    OrderTab(QWidget *, long, long, OrderTabType, int);
    ~OrderTab();

private:
    long facilityID;
    long itemID;

    OrderTabType type;

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

private slots:
    void minusClicked();
    void plusClicked();
    void deleteOrderItem();

};

#endif // ORDERTAB_H
