#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QPair>
#include <QSize>
#include <QString>
#include <QLabel>
#include <QDesktopWidget>

#define TITLE_HEIGHT 50
#define TITLE_WIDTH 70
#define RATIO 0.8
#define TAB_WIDTH 400
#define TAB_HEIGHT 500
#define PIC_WIDTH 300
#define PIC_HEIGHT 300
#define MAX_AMOUNT 10
#define RESIZE_WIDGET 20

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow(QWidget *, QApplication*);
    ~MainWindow();

    void addWidget(QWidget *, QString);
    QSize getAvailableSize();

private:
    bool resizing;
    QPoint resizeStart;
    QSize size;
    QVBoxLayout *layoutMain;
    QLabel *name_label;
    QLabel *resize_label;
    QDesktopWidget desktop;
    QRect screen;

    QWidget *settings;

    long facilityID;

    void setScreenSize(bool);
    bool canResize();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    // movingbar is listening to this signal
    void changeMovingBar(int);
    // other widgets should listen to this signal to be informed about resize of main window
    void sizeChanged_s(QSize);
    // other widgets should listen to toggle descriptions
    void toggleDescription_s();
    // for updating time every second
    void updateTime_s();
    // for updating Client data
    void updateClientData_s(long);

public slots:
    void FullScreen();
    void StepBack();
    void MoveWindow(QPair<int, int>);
    void openSettings();
    void toggleDescriptions();
};
#endif // MAINWINDOW_H
