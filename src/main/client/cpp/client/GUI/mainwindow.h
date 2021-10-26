#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPair>
#include <QSize>
#include <QString>
#include <QLabel>

#define TITLE_HEIGHT 50
#define TITLE_WIDTH 70
#define RATIO 0.8

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *, QApplication*);
    ~MainWindow();

    void addWidget(QWidget *, QString);
    QSize getAvailableSize();

private:
    Ui::MainWindow *ui;
    bool resizing;
    QPoint resizeStart;
    QSize size;
    QString window_name;
    QVBoxLayout *layoutMain;
    QLabel *name_label;

    void setScreenSize(bool);
    bool canResize();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    // movingbar is listening to this signal
    void changeMovingBar(int);
    // other widgets should listen to this signal to be informed about resize of main window
    void sizeChanged(QSize);

public slots:
    void FullScreen();
    void StepBack();
    void MoveWindow(QPair<int, int>);
};
#endif // MAINWINDOW_H
