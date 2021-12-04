/**
 * @file mainwindow.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class MainWindow
 */
#include "mainwindow.h"
#include "settings.h"
#include "itemwindow.h"
#include "orderwindow.h"
#include "welcomewindow.h"
#include "waitingscreen.h"
#include "orderpreviewwindow.h"
#include "loginscreen.h"
#include "../model/daos/FacilityDAO.h"
#include "../model/daos/OrderDAO.h"
#include "../model/daos/ClientDAO.h"

#include <QCursor>
#include <QDebug>
#include <QTimer>

void MainWindow::setScreenSize(bool fullscreen = false)
{
    setFixedSize(fullscreen ? QSize(screen.width(), screen.height()) : size);

    resizeWidgets();
}

void MainWindow::resizeWidgets()
{
    resize_label->move(width()-RESIZE_WIDGET, height()-RESIZE_WIDGET);

    emit sizeChangedTitle_s(QSize(width(), TITLE_HEIGHT));

    // signal to let other widgets know their new available space, checks whether infopanel is visible
    if (dynamic_cast<Menu *>(menu)->isInfoPanel())
        emit sizeChanged_s(QSize(width() - (INFO_PANEL_WIDTH + 3 * DEFAULT_SPACE), height() - (2 * TITLE_HEIGHT)));
    else
        emit sizeChanged_s(QSize(width() - (3 * DEFAULT_SPACE + ICON_WIDTH), height() - (2 * TITLE_HEIGHT)));
}

MainWindow::MainWindow(QWidget *parent, QApplication *app)
    : QWidget(parent)
{
    // initialize variables
    // get facilityID
    FacilityDAO dao;
    std::vector<long> facIds = dao.readFacilitiesId();
    if(facIds.size()){
        facilityID = facIds[0];
    }
    else{
        facilityID = 0;
    }

    PendingOrder pendOrd;
    pendingOrder = pendOrd;

    resizing = false;

    setStyleSheet(".MainWindow {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:1 #55EE55, stop:0 #999999);}");

    layoutMain = new QVBoxLayout(this);

    resize_label = new QLabel(this);
    resize_label->setStyleSheet("QLabel{color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255)); background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 #003300, stop:0.33 #004400, stop:0.66 #006600, stop:1 #007700);}");
    resize_label->setFixedSize(RESIZE_WIDGET, RESIZE_WIDGET);

    title = new Title(this, app);

    settings = new Settings(this);
    settings->hide();

    screen =  desktop.availableGeometry(this);
    size = QSize(screen.width() * RATIO, screen.height() * RATIO);

    //HERE WE CAN CHOOSE CLIENTS
    ClientDAO clientDAO;
    std::vector<Client> client = clientDAO.readClients();

    // initialize title of the window
    if(client.size() > 0){
        menu = new Menu(this, client[0].getId());
        pendingOrder.setClientId(client[0].getId());
    }
    else{
        menu = new Menu(this, 0);
    }
    QObject::connect(this, SIGNAL(sizeChanged_s(QSize)), menu, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(updateClientData_s(long)), menu, SLOT(updateClientData(long)));

    layoutMiddle = new QHBoxLayout();
    layoutMiddle->setSpacing(DEFAULT_SPACE);
    layoutMiddle->setContentsMargins(DEFAULT_SPACE, DEFAULT_SPACE, 0, DEFAULT_SPACE);
    layoutMiddle->setAlignment(Qt::AlignRight);

    //layoutMiddle->addWidget(current = new WelcomeWindow(this));

    // sets current widget to LoginScreen()
    layoutMiddle->addWidget(current = new LoginScreen(this));
    // buttons with menu
    layoutMiddle->addWidget(menu);

    // timer for widgets to listen to
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), menu, SLOT(updateTime()));
    timer->start(1000);

    // setup main layout
    layoutMain->setMargin(0);
    layoutMain->setSpacing(0);

    layoutMain->addWidget(title, 1, Qt::AlignTop);
    layoutMain->addLayout(layoutMiddle);

    setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::FramelessWindowHint);
    show();

    // function for custom recalculation of items
    setScreenSize();

    // move window to the middle of screen
    move(
        ((width() / RATIO) - width()) / 2,
        ((height() / RATIO) - height()) / 2);
}

MainWindow::~MainWindow()
{
    while (!past.empty())
    {
        delete past.back();
        past.pop_back();
    }
}

void MainWindow::orderFood()
{
    replaceWidget(new ItemWindow(this, facilityID, MEAL, &pendingOrder));
}

void MainWindow::orderMedicine()
{
    replaceWidget(new ItemWindow(this, facilityID, MEDICINE,&pendingOrder));
}

void MainWindow::previewOrders()
{
    replaceWidget(new OrderPreviewWindow(this, facilityID));
}

void MainWindow::previewMedicines()
{
    // temporary
    menu->hide();
    replaceWidget(new WaitingScreen(this, "testing"));
    emit start_s();
}

void MainWindow::makeOrder(long orderID, ItemType type)
{
    // we have preview of order, before we go to
    replaceWidget(new OrderWindow(this, &pendingOrder));
}

void MainWindow::confirmOrder(long orderID)
{
    //pendingOrder -> pendingToConfirmed() -> OrderDAO;
    long clientId = pendingOrder.getClientId();
    Order newOrder = pendingOrder.createConfirmedOrder();
    OrderDAO dao;
    if(!dao.createOrder(newOrder)){
        //IF ORDER WAS NOT CREATED ON SERVER
    }

    PendingOrder order;
    order.setClientId(clientId);
    pendingOrder = order;
    // we have confirmed the order, back to welcome screen probably
    replaceWidget(new WelcomeWindow(this));
}

void MainWindow::finishedWaiting()
{
    // temporary
    menu->show();
    replaceWidget(new WelcomeWindow(this));
}

void MainWindow::openOrder(PendingOrder order)
{
    // to change order
    replaceWidget(new OrderWindow(this, &order, EDIT));
}

void MainWindow::welcomeScreen()
{
    // to display welcome screen
    replaceWidget(new WelcomeWindow(this));
}

void MainWindow::openSettings()
{
    // toggle settings visibility
    if (settings->isVisible())
        settings->hide();
    else
        settings->show();
}

void MainWindow::toggleDescriptions()
{
    emit toggleDescription_s();
}

void MainWindow::changeName(QString widget_name)
{
    emit changeName_s(widget_name);
}

bool MainWindow::canResize()
{
    // bottom right corner of window where visible dragging "button" is
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

void MainWindow::stepBack()
{
    if (past.empty())
        return;

    if (menu->isHidden())
        menu->show();

    // replace currently displayed widget with previous one and delete the current one
    layoutMiddle->replaceWidget(current, past.back());
    delete current;
    current = past.back();
    current->show();
    past.pop_back();

    resizeWidgets();
}

void MainWindow::moveWindow(QPair<int, int> offset)
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

void MainWindow::fullScreen()
{
    if (screen.width() == width())
        move(
            ((width() / RATIO) - width()) / 2,
            ((height() / RATIO) - height()) / 2);
    else
        move(0, 0);

    setScreenSize(width() == screen.width() ? false : true);
}

void MainWindow::changeSize()
{
    resizeWidgets();
}

void MainWindow::replaceWidget(QWidget *next)
{
    layoutMiddle->replaceWidget(current, next);
    // we dont want to get back to WaitingScreen
    if (dynamic_cast<WaitingScreen *>(current) == nullptr)
        past.push_back(current);
    current->hide();
    current = next;
    resizeWidgets();
}
