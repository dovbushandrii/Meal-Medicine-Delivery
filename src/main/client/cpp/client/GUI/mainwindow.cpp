#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "titlebar.h"
#include "returnbar.h"
#include "movingbar.h"

#include <QDesktopWidget>
#include <QCursor>
#include <QDebug>

void MainWindow::setScreenSize(bool fullscreen = false)
{
    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    setFixedSize(fullscreen ? QSize(screen.width(), screen.height()) : size);
    name_label->setFixedWidth((width() - 4 * TITLE_WIDTH) / 2);
    emit changeMovingBar((width() - 4 * TITLE_WIDTH) / 2); //  4 as there are total of 4 buttons in title bar
    // signal to let other widgets know their new available space
    emit sizeChanged(getAvailableSize());
}

MainWindow::MainWindow(QWidget *parent, QApplication *app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // initialize variables
    ui->setupUi(this);
    resizing = false;
    QWidget *widget = new QWidget(this);
    layoutMain = new QVBoxLayout(widget);
    window_name = "Objednanie jedla";
    name_label = new QLabel(window_name, this);
    name_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name_label->setContentsMargins(50, 0, 0, 0);
    name_label->setStyleSheet("QLabel{color: black; background: transparent; font: bold italic \"Times New Roman\"; font-size:25pt}");

    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    size = QSize(screen.width() * RATIO, screen.height() * RATIO);

    // initialize title of the window
    TitleBar *titleBar = new TitleBar(this, app);
    ReturnBar *returnBar = new ReturnBar(this);
    MovingBar *movingBar = new MovingBar(this);
    QObject::connect(this, SIGNAL(changeMovingBar(int)), movingBar, SLOT(changeWidth(int)));

    QHBoxLayout *layoutTitle = new QHBoxLayout();
    QHBoxLayout *layoutTitleBar = new QHBoxLayout();
    QHBoxLayout *layoutReturnBar = new QHBoxLayout();

    // set partial title layouts
    layoutReturnBar->setAlignment(Qt::AlignLeft);
    layoutTitleBar->setAlignment(Qt::AlignRight);
    layoutReturnBar->addWidget(returnBar);
    layoutReturnBar->addWidget(name_label);
    layoutTitleBar->addWidget(movingBar);
    layoutTitleBar->addWidget(titleBar);

    // add partial layouts to the title layout
    layoutTitle->addLayout(layoutReturnBar);
    layoutTitle->addLayout(layoutTitleBar);

    // setup main layout
    layoutMain->setSpacing(0);
    layoutMain->addLayout(layoutTitle);
    layoutMain->setAlignment(Qt::AlignTop);
    layoutMain->setContentsMargins(0, 0, 0, 0);

    // set attributes of MainWindow
    setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                           "background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #009900, stop:0 #003300);}");
    setCentralWidget(widget);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // removes resize handle
    statusBar()->setSizeGripEnabled(false);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    show();

    // function for custom recalculation of items
    setScreenSize();
    move(
        ((width() / RATIO) - width()) / 2,
        ((height() / RATIO) - height()) / 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addWidget(QWidget *new_widget, QString widget_name)
{
    window_name = widget_name;
    layoutMain->addWidget(new_widget);
}

QSize MainWindow::getAvailableSize()
{
    return QSize(size.height() - TITLE_WIDTH, size.width());
}

bool MainWindow::canResize()
{
    // bottom right corner of window
    resizeStart = QCursor::pos();
    if (resizeStart.x() < pos().x() + width() - 20 || resizeStart.x() > pos().x() + width())
        return false;
    if (resizeStart.y() < pos().y() + height() - 20 || resizeStart.y() > pos().y() + height())
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
        size = QSize(std::max(width() + (QCursor::pos().x() - resizeStart.x()), 15 * TITLE_WIDTH), std::max(height() + (QCursor::pos().y() - resizeStart.y()), 12 * TITLE_HEIGHT));
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
    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);

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
    QDesktopWidget desktop;
    QRect screen =  desktop.availableGeometry(this);
    if (screen.width() == width())
        move(
            ((width() / RATIO) - width()) / 2,
            ((height() / RATIO) - height()) / 2);
    else
        move(0, 0);

    setScreenSize(width() == screen.width() ? false : true);
}

