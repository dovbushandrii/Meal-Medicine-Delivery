/**
 * @file welcomewindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class WaitingScreen, which shows initial window after signing-in
 */
#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>


class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    WelcomeWindow(QWidget *);
    ~WelcomeWindow();

private:
    QWidget *mainWidget;
    QPushButton *foodWindow;
    QPushButton *medicineWindow;
    QPushButton *ordersWindow;
    QPushButton *medicineSchedule;

    // custom override for transparency
    void paintEvent(QPaintEvent *);

signals:
    void changeName_s(QString);

public slots:
    void sizeChanged(QSize);
};

#endif // WELCOMEWINDOW_H
