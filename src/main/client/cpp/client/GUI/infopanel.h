#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDateTime>
#include <QVBoxLayout>
#include <QSize>

class InfoPanel : public QWidget
{
    Q_OBJECT
public:
    InfoPanel(MainWindow *);
    ~InfoPanel();

private:
    QLabel *timePanel;
    QWidget *mainPanel;
    QLabel *supportPanel;
    QDateTime dateTime;

    QVBoxLayout *layout;

public slots:
    void updateTime();
    void sizeChanged(QSize);
};

#endif // INFOPANEL_H
