#include "orderwindow.h"
#include "mainwindow.h"
#include "infopanel.h"

//#include "../model/daos/OrderDAO.h"

#include <QHBoxLayout>
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>

#define ORDER_TAB_HEIGHT 350

OrderWindow::OrderWindow(QWidget *parent, long facilityID, long orderID, OrderWindowType type) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->orderID = orderID;
    this->type = type;

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    setFixedSize(TAB_WIDTH + TITLE_WIDTH, TAB_HEIGHT + TITLE_HEIGHT);
    setStyleSheet(".OrderWindow {background-color: rgba(0,0,0,0);}");
    setContentsMargins(0, 0, 0, 0);

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("*{background-color: transparent}");

    totalPrice = new QLabel(this);
    totalPrice->setStyleSheet("* {font-size: 12pt; color: black; border-radius: 20px; background-color: rgba(0,0,0,60);}");
    totalPrice->setFixedSize(TAB_WIDTH, TITLE_HEIGHT);

    tabs = new QWidget(this);
    tabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tabs->setStyleSheet(".QWidget {background-color: transparent;}");

    order = new QPushButton(this);

    if (type == ORDER)
        order->setText("Objednať");
    else if (type == EDIT)
        order->setText("Upraviť");

    order->setFixedSize(2 * TITLE_WIDTH, TITLE_HEIGHT);
    order->setStyleSheet(
                             "* {font-size: 9.2pt; color: black; border-radius: 20px; background-color: rgba(0,100,0,150);} \
                             *::hover {background-color: rgba(0,180,0,230);}");

    QObject::connect(order, SIGNAL(clicked()), this, SLOT(confirmOrder()));
    QObject::connect(this, SIGNAL(confirmOrder_s(long)), parent, SLOT(confirmOrder(long)));

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet(".QScrollArea {border: 2px solid black; border-radius: 10px; background-color: rgba(0,0,0,60);}");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(tabs);
    QScrollBar *bar = new QScrollBar(scrollArea);

    bar->setStyleSheet(QString::fromUtf8("\
                                         QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                                         border-radius: 5px;\
                                         background: rgba(0,0,0,40);\
                                         }\
                                         QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\
                                         background: none;\
                                         }\
                                         QScrollBar:vertical {\
                                         border: none;\
                                         color: none;\
                                         background: transparent;\
                                         width: 12px;    \
                                         margin: 20px 0px 20px 0px;\
                                         }\
                                         QScrollBar::handle:vertical {\
                                         background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
                                         stop: 0 rgba(183, 210, 192, 255), stop: 0.5 rgba(105, 165, 5, 255), stop:1 rgba(203, 225, 0, 255));\
                                         min-height: 20px;\
                                         border-radius: 5px;\
                                         }"
                                         ));
    scrollArea->setVerticalScrollBar(bar);

    QVBoxLayout *layoutMain = new QVBoxLayout(mainWidget);
    layoutMain->setContentsMargins(0, 0, DEFAULT_SPACE, 0);
    layoutMain->setSpacing(DEFAULT_SPACE);

    QHBoxLayout *layoutUpper = new QHBoxLayout();
    layoutUpper->addWidget(totalPrice);
    layoutUpper->addWidget(order);
    layoutUpper->setSpacing(DEFAULT_SPACE);
    layoutUpper->setMargin(0);

    layout = new QVBoxLayout(tabs);
    layout->setSpacing(DEFAULT_SPACE);
    layout->setMargin(20);
    layout->setAlignment(Qt::AlignCenter);

    layoutMain->addLayout(layoutUpper);
    layoutMain->addWidget(scrollArea);

    updateAll();

    emit changeName_s(QString::fromStdString("Prehľad objednávky"));
}

OrderWindow::~OrderWindow()
{

}

void OrderWindow::sizeChanged(QSize size)
{
    // +4 @width for offsetting the borders and scrollbar
    setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH) + 4, size.height());
    mainWidget->setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH) + 4, size.height());
    order->setContentsMargins(width() - TITLE_WIDTH, height() - TITLE_HEIGHT, 0, 0);
    scrollArea->setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH), size.height() - (2 * TITLE_HEIGHT));

    emit sizeChanged_s(QSize(width() - 2 * DEFAULT_SPACE, ORDER_TAB_HEIGHT));
}

void OrderWindow::updateAll()
{
    // clear whole layout and create a new one
    for(auto widget : orderTabs)
    {
        layout->removeWidget(widget);
        delete widget;
    }

    orderTabs.clear();

//    OrderDAO orderDAO;
    // TODO this
//    std::vector<Order> orders;// = mealDAO.readMeals();

//    for (int i = 0; i < orders.size(); i++)
//    {
//        orderTabs.push_back(new OrderTab(this, facilityID, orders[i].getId(), MEAL, /*amount*/-1));
//        layout->addWidget(orderTabs.back());
//    }

    // for testing purposes only
    for (int i = 0; i < 5; i++)
    {
        orderTabs.push_back(new OrderTab(this, facilityID, /*id*/0, MEAL, /*amount*/-1));
        layout->addWidget(orderTabs.back());
    }

    // TODO update totalPrice

    sizeChanged(QSize(width(), height()));
}

void OrderWindow::updateFacility(long new_id)
{
    facilityID = new_id;

    updateAll();
}

void OrderWindow::updateOrder(long new_id)
{
    orderID = new_id;

    updateAll();
}

void OrderWindow::confirmOrder()
{
    // TODO
    // based on type
    emit confirmOrder_s(0);
}

void OrderWindow::minusClicked()
{
    // TODO update total price
    totalPrice->setText("Plus");
}

void OrderWindow::plusClicked()
{
    // TODO update total price
    totalPrice->setText("Minus");
}

void OrderWindow::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void OrderWindow::deleteOrderItem(OrderTab *to_delete)
{
    layout->removeWidget(to_delete);
    delete to_delete;
}


