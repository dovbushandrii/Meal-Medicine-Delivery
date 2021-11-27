#ifndef POPUP_H
#define POPUP_H

#include "ordertab.h"
#include "orderpreview.h"

#include <QDesktopWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>

class Popup : public QWidget
{
    Q_OBJECT

public:

    Popup(QWidget *);
    ~Popup();


private:

   QVBoxLayout *overall;
   QHBoxLayout *lay;
   QPushButton *accept;
   QPushButton *decline;
   QLabel *message;

public slots:

   void ButtonPressed();

};

#endif // POPUP_H
