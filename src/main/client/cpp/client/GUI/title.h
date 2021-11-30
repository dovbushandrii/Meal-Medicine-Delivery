/**
 * @file title.h
 * @author Rastislav Budinsky
 * @brief This file contains class Title, which holds all title items
 */
#ifndef TITLE_H
#define TITLE_H

#include "titlebar.h"
#include "returnbar.h"
#include "movingbar.h"

#include <QObject>
#include <QWidget>
#include <QLabel>

class Title : public QWidget
{
    Q_OBJECT
public:
    Title(QWidget *, QApplication *);
    ~Title();

private:
    TitleBar *titleBar;
    ReturnBar *returnBar;
    MovingBar *movingBar;
    QLabel *name_label;

signals:
    // forward signals from buttons to mainwindow
    void showMinimized_s();
    void fullScreen_s();
    void moveWindow_s(QPair<int, int>);
    void stepBack_s();

public slots:
    void changeName(QString);
    void sizeChanged(QSize);
    void showMinimized();
    void fullScreen();
    void moveWindow(QPair<int, int>);
    void stepBack();
};

#endif // TITLE_H
