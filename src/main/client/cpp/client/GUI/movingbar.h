#ifndef MOVINGBAR_H
#define MOVINGBAR_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QPair>
#include <QLabel>

class MovingBar : public QWidget
{
    Q_OBJECT
public:
    MovingBar(MainWindow *parent);

private:
    QPoint mouseNow;
    bool pressed;
    QLabel *label;

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void moved(QPair<int, int>);
    void movedToTop();

public slots:
    void changeWidth(int);
};

#endif // MOVINGBAR_H
