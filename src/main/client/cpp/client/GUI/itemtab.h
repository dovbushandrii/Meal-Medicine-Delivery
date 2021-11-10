/**
 * @file itemtab.h
 * @author Rastislav Budinsky
 * @brief This file contains class ItemTab, widget to hold information about and item
 */
#ifndef ITEMTAB_H
#define ITEMTAB_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class ItemTab : public QWidget
{
    Q_OBJECT
public:
    ItemTab(QWidget *, long, long, ItemType);
    ~ItemTab();

    std::pair<long, int> getAmount();

private:
    long facilityID;
    long mealID;
    ItemType type;

    QLabel *picture;
    QLabel *description;
    QLabel *weight;
    QLabel *price;

    QLabel *amount;
    QPushButton *minus;
    QPushButton *plus;

    QVBoxLayout *layout;
    QHBoxLayout *layoutAmount;
    QHBoxLayout *layoutPicture;

    void paintEvent(QPaintEvent *);

signals:
    void minusClicked_s();
    void plusClicked_s();

private slots:
    void minusClicked();
    void plusClicked();
};

#endif // ITEMTAB_H
