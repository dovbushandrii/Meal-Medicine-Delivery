/**
 * @file infopanel.h
 * @author Rastislav Budinsky
 * @brief This file contains class InfoPanel, which shows Personal information and data about incoming order
 */
#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "mainwindow.h"
#include "personaldata.h"
#include "nextmeal.h"
#include "settingsbutton.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSize>
#include <QDateTime>

#define INFO_PANEL_WIDTH (5*TITLE_WIDTH)

class InfoPanel : public QWidget
{
    Q_OBJECT
public:
    InfoPanel(QWidget *, long = 0L);
    ~InfoPanel();

private:
    QLabel *personalDetails;
    QLabel *timePanel;
    QDateTime dateTime;
    QWidget *mainPanel;
    QLabel *supportPanel;
    QPushButton *hideButton;

    Client client;
    PersonalData *personalData;
    NextMeal *nextMeal;
    SettingsButton *settings;

    QVBoxLayout *layout;
    QVBoxLayout *layoutMiddle;

signals:
    void updateClientData_s(long);
    void updateTime_s();
    void switchContent_s();

public slots:
    void sizeChanged(QSize);
    void updateClientData(long);
    void updateTime();

// toggling between icons and infopanel
private slots:
    void openIcons();
};

#endif // INFOPANEL_H
