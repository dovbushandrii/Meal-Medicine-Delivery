/**
 * @file returnbar.h
 * @author Rastislav Budinsky
 * @brief This file contains class ReturnBar, which should be used as return button in MainWindow
 */
#ifndef RETURNBAR_H
#define RETURNBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class ReturnBar : public QWidget
{
    Q_OBJECT
public:
    ReturnBar(QWidget *);

private:
    QPushButton *back_button;

// signal signalizing button push is directly in .cpp

public slots:
    void toggleDescription();
};

#endif // RETURNBAR_H
