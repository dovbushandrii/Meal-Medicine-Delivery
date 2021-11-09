/**
 * @file foodtab.h
 * @author Rastislav Budinsky
 * @brief This file contains class FoodTab, widget to hold information about and item
 */
#ifndef FOODTAB_H
#define FOODTAB_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class FoodTab : public QWidget
{
    Q_OBJECT
public:
    FoodTab(QWidget *, long, long);
    ~FoodTab();

    std::pair<long, int> getAmount();

private:
    long facilityID;
    long mealID;

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

#endif // FOODTAB_H
