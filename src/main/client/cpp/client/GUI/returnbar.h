#ifndef RETURNBAR_H
#define RETURNBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ReturnBar : public QWidget
{
    Q_OBJECT
public:
    ReturnBar(QWidget *);

private:
    QHBoxLayout *layout;
    QPushButton *back_button;

public slots:
    void toggleDescription();
};

#endif // RETURNBAR_H
