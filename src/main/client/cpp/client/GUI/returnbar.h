#ifndef RETURNBAR_H
#define RETURNBAR_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ReturnBar : public QWidget
{
    Q_OBJECT
public:
    ReturnBar(MainWindow *);

private:
    QHBoxLayout *layout;
    QPushButton *back_button;
};

#endif // RETURNBAR_H
