#ifndef SETTINGS_H
#define SETTINGS_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Settings : public QWidget
{
    Q_OBJECT
public:
    Settings(MainWindow *);
    ~Settings();

private:
    QPushButton *descriptions;
    QHBoxLayout *layoutMain;
    QVBoxLayout *layoutLeft;
    QVBoxLayout *layoutRight;

};

#endif // SETTINGS_H
