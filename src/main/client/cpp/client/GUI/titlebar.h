#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QApplication>

class TitleBar: public QWidget
{
    Q_OBJECT
public:
    TitleBar(MainWindow *, QApplication *);

private:
    QHBoxLayout *layout;
    QPushButton *close;
    QPushButton *maximize;
    QPushButton *minimize;

signals:
    void toFullScreen();

private slots:
    void Maximize();
};

#endif // TITLEBAR_H
