/**
 * @file orderpreviewwindow.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class OrderPreviewWindow
 */
#include "orderpreviewwindow.h"
#include "mainwindow.h"
#include "itemtab.h"

#include <QScrollBar>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <cmath>

OrderPreviewWindow::OrderPreviewWindow(QWidget *parent, long facilityID) : QWidget(parent)
{
    this->facilityID = facilityID;

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(this, SIGNAL(openOrder_s(long)), parent, SLOT(openOrder(long)));
    setFixedSize(TAB_WIDTH + TITLE_WIDTH, TAB_HEIGHT + TITLE_HEIGHT);
    setStyleSheet(".OrderPreviewWindow {background-color: rgba(0,0,0,0);}");
    setContentsMargins(0, 0, 0, 0);

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("*{background-color: transparent}");

    tabs = new QWidget(this);
    tabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tabs->setStyleSheet(".QWidget {background-color: transparent;}");

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

    layout = new QGridLayout(tabs);
    layout->setSpacing(DEFAULT_SPACE);
    layout->setAlignment(Qt::AlignCenter);
    layout->setMargin(DEFAULT_SPACE);

    layoutMain->addWidget(scrollArea);

    // fill orders
    // for testing purposes only
    for (int i = 0; i < 5; i++)
    {
        orders.push_back(new OrderPreview(this, 0));
        layout->addWidget(orders.back());
    }

    emit changeName_s(QString::fromStdString("Prehľad objednávok"));
}

OrderPreviewWindow::~OrderPreviewWindow()
{

}

void OrderPreviewWindow::openOrder(long orderID)
{
    // TODO
    emit openOrder_s(orderID);
}

void OrderPreviewWindow::sizeChanged(QSize size)
{
    // +4 @width for offsetting the borders and scrollbar
    setFixedSize(size.width() + 4, size.height());
    mainWidget->setFixedSize(size.width() + 4, size.height());
    scrollArea->setFixedSize(size.width(), size.height() - (2 * TITLE_HEIGHT));

    if (orders.empty())
        return;

    updateAll();
}

void OrderPreviewWindow::updateAll()
{
    if (orders.empty())
        return;

    int columns = width() - (2 * layout->margin() + 2 * DEFAULT_SPACE);
    columns = std::floor(1.0 * columns / (orders[0]->width() + DEFAULT_SPACE));
    int rows = std::ceil(1.0 * orders.size() / columns);

    layout->setHorizontalSpacing(columns <= 0 ? DEFAULT_SPACE :
                                      (width() - (2 * layout->margin() + columns * (orders[0]->width() + DEFAULT_SPACE))) / columns);

    tabs->setFixedSize(width(), rows * (orders[0]->height() + DEFAULT_SPACE) + (3 * DEFAULT_SPACE));

    if (rows == 0 || columns == 0)
        return;

    for (int i = 0; i < orders.size(); i++)
        layout->addWidget(orders[i], i / columns, i % columns);

    for(int c=0; c < layout->columnCount(); c++) layout->setColumnStretch(c,1);
    for(int r=0; r < layout->rowCount(); r++)  layout->setRowStretch(r,1);
}

void OrderPreviewWindow::deleteOrderItem(OrderPreview *to_delete)
{
    layout->removeWidget(to_delete);
    for (int i = 0; i < orders.size(); i++)
        if (orders[i] == to_delete)
        {
            orders.erase(orders.begin() + i);
            break;
        }
    delete to_delete;
    updateAll();
}

void OrderPreviewWindow::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
