#include "returnbar.h"

#include <QGraphicsBlurEffect>

ReturnBar::ReturnBar(MainWindow *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    back_button = new QPushButton("Krok Späť", this);
    setLayout(layout);
    back_button->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    back_button->setStyleSheet("* {font-size: 9.2pt; color: black; border-bottom-right-radius: 10px; background-color: rgba(230,230,0,180); image: url(../imgs/return_mirrored_transparent.png);}");

    // create effects
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(1.5);
    back_button->setGraphicsEffect(blur);

    // set up layout
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setDirection(QBoxLayout::LeftToRight);
    layout->addWidget(back_button);

    QObject::connect(back_button, SIGNAL(clicked()), parent, SLOT(StepBack()));
}

void ReturnBar::toggleDescription()
{
    if (back_button->text() == "")
        back_button->setText("Krok Späť");
    else
        back_button->setText("");
}
