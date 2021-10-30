#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "titlebar.h"
#include "returnbar.h"
#include "movingbar.h"
#include "infopanel.h"
#include "settings.h"
#include "foodtab.h"

#include <QCursor>
#include <QDebug>
#include <QTimer>

void MainWindow::setScreenSize(bool fullscreen = false)
{
    setFixedSize(fullscreen ? QSize(screen.width(), screen.height()) : size);
    name_label->setFixedWidth((width() - 4 * TITLE_WIDTH) / 2);
    resize_label->move(width()-RESIZE_WIDGET, height()-RESIZE_WIDGET);
    emit changeMovingBar((width() - 4 * TITLE_WIDTH) / 2); //  4 as there are total of 4 buttons in title bar
    // signal to let other widgets know their new available space
    emit sizeChanged_s(getAvailableSize());
}

MainWindow::MainWindow(QWidget *parent, QApplication *app)
    : QWidget(parent)
{
    // initialize variables
    // get facilityID
    facilityID = 0;

    resizing = false;

    setStyleSheet(".MainWindow {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #009900, stop:0 #003300);}");

    layoutMain = new QVBoxLayout(this);
    name_label = new QLabel(QString::fromStdString("Domov"), this);
    name_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name_label->setContentsMargins(50, 0, 0, 0);
    name_label->setStyleSheet("QLabel{color: black; background: transparent; text-decoration: underline; font: bold italic underline \"Times New Roman\"; font-size:25pt}");

    resize_label = new QLabel(this);
    resize_label->setStyleSheet("QLabel{color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 #003300, stop:0.33 #004400, stop:0.66 #006600, stop:1 #007700);}");
    resize_label->setFixedSize(RESIZE_WIDGET, RESIZE_WIDGET);

    settings = new Settings(this);
    settings->hide();

    screen =  desktop.availableGeometry(this);
    size = QSize(screen.width() * RATIO, screen.height() * RATIO);

    // initialize title of the window
    TitleBar *titleBar = new TitleBar(this, app);
    ReturnBar *returnBar = new ReturnBar(this);
    MovingBar *movingBar = new MovingBar(this);
    InfoPanel *infoPanel = new InfoPanel(this);
    QObject::connect(this, SIGNAL(changeMovingBar(int)), movingBar, SLOT(changeWidth(int)));
    QObject::connect(this, SIGNAL(toggleDescription_s()), titleBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(toggleDescription_s()), returnBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(toggleDescription_s()), movingBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(sizeChanged_s(QSize)), infoPanel, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(updateClientData_s(long)), infoPanel, SLOT(updateClientData(long)));

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), infoPanel, SLOT(updateTime()));
    timer->start(1000);

    QHBoxLayout *layoutTitle = new QHBoxLayout();
    QHBoxLayout *layoutTitleBar = new QHBoxLayout();
    QHBoxLayout *layoutReturnBar = new QHBoxLayout();
    QHBoxLayout *layoutMiddle = new QHBoxLayout();

    // set partial title layouts
    layoutReturnBar->setAlignment(Qt::AlignLeft);
    layoutTitleBar->setAlignment(Qt::AlignRight);
    layoutReturnBar->addWidget(returnBar);
    layoutReturnBar->addWidget(name_label);
    layoutTitleBar->addWidget(movingBar);
    layoutTitleBar->addWidget(titleBar);

    // middle layouts
    layoutMiddle->setAlignment(Qt::AlignRight);
    FoodTab *foodTab = new FoodTab(this, 0, 0);
    layoutMiddle->addWidget(foodTab);
    layoutMiddle->addWidget(infoPanel);

    // add partial layouts to the title layout
    layoutTitle->addLayout(layoutReturnBar);
    layoutTitle->addLayout(layoutTitleBar);

    // setup main layout
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);
    layoutMain->setAlignment(Qt::AlignTop);

    layoutMain->addLayout(layoutTitle);
    layoutMain->addLayout(layoutMiddle);

    setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::FramelessWindowHint);
    show();

    // function for custom recalculation of items
    setScreenSize();
    move(
        ((width() / RATIO) - width()) / 2,
        ((height() / RATIO) - height()) / 2);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSettings()
{
    if (settings->isVisible())
        settings->hide();
    else
        settings->show();
}

void MainWindow::toggleDescriptions()
{
    emit toggleDescription_s();
}

void MainWindow::addWidget(QWidget *new_widget, QString widget_name)
{
    name_label->setText(widget_name);
    layoutMain->addWidget(new_widget);
}

QSize MainWindow::getAvailableSize()
{
    return QSize(width() - TITLE_WIDTH, height());
}

bool MainWindow::canResize()
{
    // bottom right corner of window
    resizeStart = QCursor::pos();
    if (resizeStart.x() < pos().x() + width() - RESIZE_WIDGET || resizeStart.x() > pos().x() + width())
        return false;
    if (resizeStart.y() < pos().y() + height() - RESIZE_WIDGET || resizeStart.y() > pos().y() + height())
        return false;
    return true;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    (void)event;
    resizing = canResize();
    if (resizing)
        setCursor(Qt::SizeFDiagCursor);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    (void)event;
    if (resizing)
    {
        resizing = false;
        // max() to maintain minimal size
        size = QSize(std::max(width() + (QCursor::pos().x() - resizeStart.x()), static_cast<int> ((float)screen.width() * RATIO)), std::max(height() + (QCursor::pos().y() - resizeStart.y()), static_cast<int> ((float)screen.height() * RATIO)));
        setScreenSize();
        unsetCursor();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{
    if (!resizing)
    {
        if (canResize())
            setCursor(Qt::SizeFDiagCursor);
        else
            unsetCursor();
    }
}

void MainWindow::StepBack()
{
    // TO DO
}

void MainWindow::MoveWindow(QPair<int, int> offset)
{
    // we are fullscreen, need to move to the right top corner
    if (width() == screen.width())
    {
        int buttons_right = 3 * TITLE_WIDTH;
        int buttons_left = 1 * TITLE_WIDTH;
        float mouse_ratio = 1.0*(QCursor::pos().x() - buttons_left) / (width() - (buttons_right + buttons_left));
        int screen_ratio_new = width() * (1.0 * size.width() /  width()) - (buttons_right + buttons_left);
        int a = QCursor::pos().x() - (buttons_left + screen_ratio_new * mouse_ratio);
        move(a, 0);
        setScreenSize();
    }
    else
    {
        QPoint pos = this->parentWidget()->mapToGlobal(this->pos());
        move(pos.x() + offset.first, pos.y() + offset.second);
    }
}

void MainWindow::FullScreen()
{
    if (screen.width() == width())
        move(
            ((width() / RATIO) - width()) / 2,
            ((height() / RATIO) - height()) / 2);
    else
        move(0, 0);

    setScreenSize(width() == screen.width() ? false : true);
}

