/**
 * @file titlebar.h
 * @author Rastislav Budinsky
 * @brief This file contains class TitleBar, which creates minimize, maximize and close button
 */
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QApplication>

class TitleBar: public QWidget
{
    Q_OBJECT
public:
    TitleBar(QWidget *, QApplication *);

private:
    QHBoxLayout *layout;
    QPushButton *close;
    QPushButton *maximize;
    QPushButton *minimize;

signals:
    void toFullScreen();

public slots:
    void toggleDescription();

private slots:
    void Maximize();
};

#endif // TITLEBAR_H
