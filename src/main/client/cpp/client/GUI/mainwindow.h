/**
 * @file mainwindow.h
 * @author Rastislav Budinsky
 * @brief This file contains class MainWindow, which is main window of the application
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "title.h"
#include "menu.h"
#include "../model/entities/PendingOrder.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPair>
#include <QSize>
#include <QString>
#include <QLabel>
#include <QDesktopWidget>
#include <vector>

#define TITLE_HEIGHT 60
#define TITLE_WIDTH 80
#define RATIO 0.8
#define TAB_WIDTH 400
#define TAB_HEIGHT 500
#define PIC_WIDTH 300
#define PIC_HEIGHT 300
#define MAX_AMOUNT 10
#define RESIZE_WIDGET 20
#define DEFAULT_SPACE 25
#define AMOUNT_WIDTH 40
#define AMOUNT_HEIGHT AMOUNT_WIDTH
#define ICON_WIDTH 80
#define ICON_HEIGHT ICON_WIDTH
#define DECIMALJESUS(a) (std::to_string((a)).substr(0,std::to_string((a)).find(".") + 3))


enum ItemType {MEAL, MEDICINE};

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow(QWidget *, QApplication*);
    ~MainWindow();

private:
    bool resizing;
    QPoint resizeStart;
    QSize size;
    QVBoxLayout *layoutMain;
    QHBoxLayout *layoutMiddle;  // layout where widgets are switched
    QLabel *resize_label;
    QDesktopWidget desktop;
    QRect screen;

    QWidget *menu;
    Title *title;
    QWidget *settings;
    QWidget *current;       // currently displayed widget

    // for steps back
    std::vector<QWidget *> past;    // widgets displayed in the past used for Back button action

    long facilityID;        // ID of currently used facility
    PendingOrder pendingOrder;

    void setScreenSize(bool);
    void resizeWidgets();
    bool canResize();
    void replaceWidget(QWidget *);  // for replacing currently displayed widget

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    // movingbar is listening to this signal
    void changeMovingBar(int);
    // other widgets should listen to this signal to be informed about resize of main window
    void sizeChanged_s(QSize);
    // other widgets from Title should listen to this signal to be informed about resize of main window
    void sizeChangedTitle_s(QSize);
    // other widgets should listen to toggle descriptions
    void toggleDescription_s();
    // for updating time every second
    void updateTime_s();
    // for updating Client data
    void updateClientData_s(long);
    // for changing name of window
    void changeName_s(QString);
    // this should be used in async waiting
    void start_s();

public slots:
    // to got fullscreen
    void fullScreen();
    void stepBack();
    void moveWindow(QPair<int, int>);
    void openSettings();
    void toggleDescriptions();
    // if widgets want to change Name should call this SLOT
    void changeName(QString);
    // internal SIGNALS for communication of next widget
    void orderFood();
    void orderMedicine();
    void previewOrders();
    void previewMedicines();
    void makeOrder(long, ItemType);
    void confirmOrder(long);
    void finishedWaiting();
    void openOrder(PendingOrder);
    void changeSize();
    void welcomeScreen();
};
#endif // MAINWINDOW_H
