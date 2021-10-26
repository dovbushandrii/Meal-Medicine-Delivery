#include "movingbar.h"

#include <QMouseEvent>
#include <QHBoxLayout>
#include <QCursor>
#include <QGraphicsBlurEffect>

MovingBar::MovingBar(MainWindow *parent) : QWidget(parent)
{
    pressed = false;
    setCursor(Qt::OpenHandCursor);
    setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);

    // set up layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setDirection(QBoxLayout::RightToLeft);
    layout->setAlignment(Qt::AlignRight);

    // create label for moving bar, initialize effects
    label = new QLabel(this);
    label->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(1.5);
    label->setGraphicsEffect(blur);
    label->setStyleSheet("QLabel{border-bottom-left-radius: 30px; background-color: rgba(97,63,135,180); background-image: url(../imgs/dots_transparent.png) no-repeat center center fixed;}");

    layout->addWidget(label);

    setLayout(layout);

    QObject::connect(this, SIGNAL(moved(QPair<int, int>)), parent, SLOT(MoveWindow(QPair<int, int>)));
    QObject::connect(this, SIGNAL(movedToTop()), parent, SLOT(FullScreen()));
}

void MovingBar::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    pressed = true;
    setCursor(Qt::ClosedHandCursor);
    mouseNow = QCursor::pos();
}

void MovingBar::mouseReleaseEvent(QMouseEvent *event)
{
    (void) event;
    pressed = false;
    setCursor(Qt::OpenHandCursor);
    if (QCursor::pos().y() == 0)
        emit movedToTop();
}

void MovingBar::mouseMoveEvent(QMouseEvent *event)
{
    (void) event;
    if (pressed)
    {
        QPoint mouseBefore = mouseNow;
        mouseNow = QCursor::pos();
        emit moved({mouseNow.x() - mouseBefore.x(), mouseNow.y() - mouseBefore.y()});
    }
}

void MovingBar::changeWidth(int width)
{
    setFixedSize(width, TITLE_HEIGHT);
    label->setFixedSize(width, TITLE_HEIGHT);
}
