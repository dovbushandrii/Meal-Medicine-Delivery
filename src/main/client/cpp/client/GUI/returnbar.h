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

public slots:
    void toggleDescription();
};

#endif // RETURNBAR_H
