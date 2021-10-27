#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "mainwindow.h"
#include "personaldata.h"
#include "nextmeal.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDateTime>
#include <QVBoxLayout>
#include <QSize>

#define INFO_PANEL_WIDTH (5*TITLE_WIDTH)

class InfoPanel : public QWidget
{
    Q_OBJECT
public:
    InfoPanel(MainWindow *, long = 0L);
    ~InfoPanel();

private:
    QLabel *timePanel;
    QWidget *mainPanel;
    QLabel *supportPanel;
    QDateTime dateTime;

    Client client;
    PersonalData *personalData;
    NextMeal *nextMeal;

    QVBoxLayout *layout;
    QVBoxLayout *layoutMiddle;

signals:
    void updateClientData_s(long);
    void updateTime_s();

public slots:
    void updateTime();
    void sizeChanged(QSize);
    void updateClientData(long);
};

#endif // INFOPANEL_H
