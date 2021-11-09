#ifndef MENU_H
#define MENU_H

#include "infopanel.h"
#include "infopanelicons.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *, long = 0);
    ~Menu();

    bool isInfoPanel();

private:
    QVBoxLayout *layout;

    long clientID;
    bool showingIcons;

    QWidget *infoPanel;
    QWidget *icons;

signals:
    void updateTime_s();
    void updateClientData_s(long);
    void sizeChanged_s(QSize);
    void openSettings_s();
    void changeSize_s();

public slots:
    void updateTime();
    void sizeChanged(QSize);
    void updateClientData(long);
    void openSettings();
    void switchContent();
};

#endif // MENU_H
