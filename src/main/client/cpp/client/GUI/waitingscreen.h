/**
 * @file waitingscreen.h
 * @author Rastislav Budinsky
 * @brief This file contains class WaitingScreen, which should be used for async waiting
 *      @note Use this screen for async waiting
 */
#ifndef WAITINGSCREEN_H
#define WAITINGSCREEN_H

#include <QObject>
#include <QWidget>

class WaitingScreen : public QWidget
{
    Q_OBJECT
public:
    WaitingScreen(QWidget *, QString);
    ~WaitingScreen();

private:
    QWidget *mainWidget;
    // custom override for transparency
    void paintEvent(QPaintEvent *);

signals:
    // emits upon succesfully loading content
    void finishedWaiting_s();
    // starts to wait
    void wait();
    void changeName_s(QString);

public slots:
    void sizeChanged(QSize);
    // when should start to load data
    void start();

};

#endif // WAITINGSCREEN_H
