/**
 * @file popup.h
 * @author Samuel Hribik
 * @brief Definitions of slots and signals for Popup window,
 *        which is created when user tries to remove item from OrderPreview of OrderTab
 */

#ifndef POPUP_H
#define POPUP_H

#include "ordertab.h"
#include "orderpreview.h"

#include <QDesktopWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

enum Typ {regi, discard};

class Popup : public QWidget
{
    Q_OBJECT

public:

    Popup(QWidget *, Typ);
    ~Popup();


private:

   QVBoxLayout *overall;
   QHBoxLayout *lay;
   QPushButton *accept;
   QPushButton *decline;
   QLabel *message;
   QLabel *password;
   QLabel *email;
   QLineEdit *line;
   QLineEdit *pass_line;
   QLineEdit *email_line;

   void paintEvent(QPaintEvent *);

public slots:

   void ButtonPressed();

};

#endif // POPUP_H
