#ifndef NEXTMEAL_H
#define NEXTMEAL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "../model/entities/Meal.h"

class NextMeal : public QWidget
{
    Q_OBJECT
public:
    NextMeal(QWidget *);
    ~NextMeal();

private:
    Meal meal;
    QLabel *title;
    QLabel *time;
    QLabel *details;
    bool pressed;

    QVBoxLayout *layout;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void showOrderDetails();

public slots:
    void updateNextMeal();
    void updateTime();
};

#endif // NEXTMEAL_H
