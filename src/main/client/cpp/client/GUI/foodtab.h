#ifndef FOODTAB_H
#define FOODTAB_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#define AMOUNT_WIDTH 30
#define AMOUNT_HEIGHT AMOUNT_WIDTH

class FoodTab : public QWidget
{
    Q_OBJECT
public:
    FoodTab(QWidget *, long, long);
    ~FoodTab();

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

private slots:
    void minusClicked();
    void plusClicked();
};

#endif // FOODTAB_H
