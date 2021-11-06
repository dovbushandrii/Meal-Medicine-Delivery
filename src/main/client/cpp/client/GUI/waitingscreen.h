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
    void paintEvent(QPaintEvent *);

signals:
    void finishedWaiting_s();
    void wait();
    void changeName_s(QString);

public slots:
    void sizeChanged(QSize);
    void start();

};

#endif // WAITINGSCREEN_H
