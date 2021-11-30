/**
 * @file itemwindow.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class ItemWindow
 */
#include "itemwindow.h"
#include "infopanel.h"

#include "../model/daos/MealDAO.h"
#include "../model/entities/Meal.h"

#include <cmath>
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

ItemWindow::ItemWindow(QWidget *parent, long facilityID, ItemType type) : QWidget(parent)
{
    this->facilityID = facilityID;
    this->type = type;

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(this, SIGNAL(makeOrder_s(long, ItemType)), parent, SLOT(makeOrder(long, ItemType)));
    setFixedSize(TAB_WIDTH + TITLE_WIDTH, TAB_HEIGHT + TITLE_HEIGHT);
    setStyleSheet(".ItemWindow {background-color: rgba(0,0,0,0);}");

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet(".QWidget{background-color: rgba(0,0,0,0);}");
    mainWidget->setFixedSize(width(), height());

    totalPreview = new QLabel(this);
    totalPreview->setStyleSheet("* {font-size: 12pt; color: black; border-radius: 20px; background-color: rgba(0,0,0,60);}");
    totalPreview->setFixedSize(TAB_WIDTH, TITLE_HEIGHT);

    tabs = new QWidget(this);
    tabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tabs->setStyleSheet(".QWidget {background-color: transparent;}");

    totalOrder = 0;
    order = new QPushButton("Prehľad objednávky", this);
    order->setFixedSize(2 * TITLE_WIDTH+70, TITLE_HEIGHT);
    order->setStyleSheet(
                             "* {font : 'Arial'; font-size: 12.5pt; color: black; border-radius: 20px; background-color: rgba(0,0,0,80);} \
                             *::hover {border: solid black 2px; background-color: rgba(0,0,0,120);}");

    QObject::connect(order, SIGNAL(clicked()), this, SLOT(makeOrder()));
//    QObject::connect(this, SIGNAL(makeOrder_s(std::vector<Order>)), parent, SLOT(makeOrder(std::vector<Order>)));

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

    QStackedLayout *layoutStacked = new QStackedLayout(scrollArea);
    layoutStacked->setStackingMode(QStackedLayout::StackAll);
    layoutStacked->setContentsMargins(50, 50, 50, 50);

    layout = new QGridLayout(tabs);
    layout->setSpacing(DEFAULT_SPACE);
    layout->setMargin(20);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QVBoxLayout *layoutMain = new QVBoxLayout(mainWidget);
    layoutMain->setContentsMargins(0, 0, DEFAULT_SPACE, 0);
    layoutMain->setSpacing(DEFAULT_SPACE);

    QHBoxLayout *layoutUpper = new QHBoxLayout();
    layoutUpper->addWidget(totalPreview);
    layoutUpper->addWidget(order);
    layoutUpper->setSpacing(DEFAULT_SPACE);
    layoutUpper->setMargin(0);

    layoutMain->addLayout(layoutUpper);
    layoutMain->addWidget(scrollArea);

    // fill foodTabs
    // for testing purposes only
    // TODO create ItemTabs and send them proper parameters of IDs
    for (int i = 0; i < 5; i++)
    {
        foodTabs.push_back(new ItemTab(this, facilityID, 0, type));
    }

    emit changeName_s(QString::fromStdString("Objednávanie jedla"));
}

ItemWindow::~ItemWindow()
{

}

void ItemWindow::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ItemWindow::sizeChanged(QSize size)
{
    for (auto widget : foodTabs)
        layout->removeWidget(widget);

    // +4 @width for off-setting the borders and scrollbar
    setFixedSize(size.width() + 4, size.height());
    mainWidget->setFixedSize(size.width() + 4, size.height());
    order->setContentsMargins(width(), height() - TITLE_HEIGHT, 0, 0);

    scrollArea->setFixedSize(size.width(), size.height() - (2 * TITLE_HEIGHT));

    if (foodTabs.empty())
        return;

    int columns = size.width() - (2 * layout->margin());
    columns = std::floor(1.0 * columns / (foodTabs[0]->width() + DEFAULT_SPACE));
    int rows = std::ceil(1.0 * foodTabs.size() / columns);

    layout->setHorizontalSpacing(columns <= 0 ? DEFAULT_SPACE :
                                      (size.width() - (2 * layout->margin() + columns * (foodTabs[0]->width() + DEFAULT_SPACE))) / columns);

    tabs->setFixedSize(size.width(), rows * (foodTabs[0]->height() + DEFAULT_SPACE) + (3 * DEFAULT_SPACE));

    if (rows == 0 || columns == 0)
        return;

    for (int i = 0; i < foodTabs.size(); i++)
        layout->addWidget(foodTabs[i], i / columns, i % columns);

    for(int c=0; c < layout->columnCount(); c++) layout->setColumnStretch(c,1);
    for(int r=0; r < layout->rowCount(); r++)  layout->setRowStretch(r,1);
}

void ItemWindow::updateFacility(long new_id)
{
    facilityID = new_id;
    // clear whole layout and create a new one
    for(auto widget : foodTabs)
    {
        layout->removeWidget(widget);
        delete widget;
    }

    foodTabs.clear();

    MealDAO mealDAO;
    // TODO get new Items
    std::vector<Meal> meals;// = mealDAO.readMeals();

    for (int i = 0; i < meals.size(); i++)
    {
        foodTabs.push_back(new ItemTab(this, facilityID, meals[i].getId(), type));
    }

    // for testing purposes only
    // TODO remove this when mealDAO works
    for (int i = 0; i < 5; i++)
    {
        foodTabs.push_back(new ItemTab(this, facilityID, 0, type));
    }

    sizeChanged(QSize(width(), height()));
}

void ItemWindow::makeOrder()
{
    // TODO
//    std::vector<Order> meals;
//    for (auto meal : foodTabs)
//    {
//        std::pair<long, int> orderedMeal = meal->getAmount();
//        // add meals to order;
//    }
    // TODO
    emit makeOrder_s(0, type);
}

void ItemWindow::minusClicked()
{
    if (totalOrder == 0)
        return;
    totalOrder--;
    if (totalOrder)
        order->setText(QString::fromStdString("Objednať\n(" + std::to_string(totalOrder) + ")"));
    else
        order->setText("Objednať");
}

void ItemWindow::plusClicked()
{
    totalOrder++;
    order->setText(QString::fromStdString("Objednať\n(" + std::to_string(totalOrder) + ")"));
}
