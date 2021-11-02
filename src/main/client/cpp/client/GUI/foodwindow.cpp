#include "foodwindow.h"
#include "infopanel.h"
#include "mainwindow.h"

#include "../model/daos/MealDAO.h"
#include "../model/entities/Meal.h"

#include <cmath>
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>
#include <QStackedLayout>

#define DEFAULT_SPACE 25

FoodWindow::FoodWindow(QWidget *parent, long facilityID) : QWidget(parent)
{
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    setFixedSize(TAB_WIDTH + TITLE_WIDTH, TAB_HEIGHT + TITLE_HEIGHT);
    setStyleSheet(".FoodWindow {border: 2px solid black; border-radius: 10px; background-color: rgba(0,0,0,60);}");

    tabs = new QWidget(this);
    tabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tabs->setStyleSheet(".QWidget {background-color: transparent;}");

    totalOrder = 0;
    order = new QPushButton("Objednať", this);
    order->setFixedSize(TITLE_WIDTH, TITLE_HEIGHT);
    order->setStyleSheet(
                             "* {font-size: 9.2pt; color: black; border-radius: 20px; background-color: rgba(0,100,0,150);} \
                             *::hover {background-color: rgba(0,180,0,230);}");

    QObject::connect(order, SIGNAL(clicked()), this, SLOT(makeOrder()));
//    QObject::connect(this, SIGNAL(makeOrder_s(std::vector<Order>)), parent, SLOT(makeOrder(std::vector<Order>)));

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("* {border: 0px; background: transparent;}");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(tabs);
    QScrollBar *bar = new QScrollBar(scrollArea);

    // from https://forum.qt.io/topic/961/style-the-scrollbar-of-qlistview/6
    bar->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\
                                         background: darkgreen;\
                                         width: 15px;\
                                         margin: 20px 0px 20px 0px;\
                                         border-radius: 10px;\
                                         }\
                                         QScrollBar::handle:vertical {\
                                         background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
                                         stop: 0 rgba(183, 210, 192, 255), stop: 0.5 rgba(105, 165, 5, 255), stop:1 rgba(203, 225, 0, 255));\
                                         min-height: 20px;\
                                         border-radius: 10px;\
                                         }\
                                         QScrollBar::add-line:vertical {\
                                         background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
                                         stop: 0 rgba(183, 210, 192, 255), stop: 0.5 rgba(105, 165, 5, 255), stop:1 rgba(203, 225, 0, 255));\
                                         height: 0px;\
                                         subcontrol-position: bottom;\
                                         subcontrol-origin: margin;\
                                         }\
                                         QScrollBar::sub-line:vertical {\
                                         background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
                                         stop: 0 rgba(183, 210, 192, 255), stop: 0.5 rgba(105, 165, 5, 255), stop:1 rgba(203, 225, 0, 255));\
                                         height: 0px;\
                                         subcontrol-position: top;\
                                         subcontrol-origin: margin;\
                                         }"
                                         ));
    scrollArea->setVerticalScrollBar(bar);

    QStackedLayout *layoutStacked = new QStackedLayout(scrollArea);
    layoutStacked->setStackingMode(QStackedLayout::StackAll);
    layoutStacked->setContentsMargins(50, 50, 50, 50);
    layoutStacked->addWidget(order);

    layout = new QGridLayout(tabs);
    layout->setSpacing(DEFAULT_SPACE);
    layout->setMargin(20);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    updateFacility(facilityID);

    emit changeName_s(QString::fromStdString("Objednávanie jedla"));
}

FoodWindow::~FoodWindow()
{

}

void FoodWindow::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FoodWindow::sizeChanged(QSize size)
{
    for (auto widget : foodTabs)
        layout->removeWidget(widget);

    // +4 @width for offsetting the borders and scrollbar
    setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH) + 4, size.height() - 2 * TITLE_HEIGHT);
    order->setContentsMargins(width() - TITLE_WIDTH, height() - TITLE_HEIGHT, 0, 0);

    scrollArea->setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH), size.height() - 2 * TITLE_HEIGHT);
    int columns = size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH) - (2 * layout->margin());
    columns = std::floor(1.0 * columns / (TAB_WIDTH + DEFAULT_SPACE));
    int rows = std::ceil(1.0 * foodTabs.size() / columns);

    layout->setHorizontalSpacing(columns <= 0 ? DEFAULT_SPACE :
                                      (size.width() - (2 * layout->margin() + TITLE_WIDTH + INFO_PANEL_WIDTH + columns * TAB_WIDTH)) / columns);

    tabs->setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH), (rows + 1) * TAB_HEIGHT);

    if (rows == 0 || columns == 0)
        return;

    for (int i = 0; i < foodTabs.size(); i++)
        layout->addWidget(foodTabs[i], i / columns, i % columns);

    for(int c=0; c < layout->columnCount(); c++) layout->setColumnStretch(c,1);
    for(int r=0; r < layout->rowCount(); r++)  layout->setRowStretch(r,1);
}

void FoodWindow::updateFacility(long new_id)
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
    // TODO this
    std::vector<Meal> meals;// = mealDAO.readMeals();

    for (int i = 0; i < meals.size(); i++)
    {
        foodTabs.push_back(new FoodTab(this, facilityID, meals[i].getId()));
    }

    // for testing purposes only
    for (int i = 0; i < 5; i++)
    {
        foodTabs.push_back(new FoodTab(this, facilityID, 0));
    }

    sizeChanged(QSize(width(), height()));
}

void FoodWindow::makeOrder()
{
//    std::vector<Order> meals;
//    for (auto meal : foodTabs)
//    {
//        std::pair<long, int> orderedMeal = meal->getAmount();
//        // add meals to order;
//    }
//    emit ordered_s(meals);
}

void FoodWindow::minusClicked()
{
    if (totalOrder == 0)
        return;
    totalOrder--;
    if (totalOrder)
        order->setText(QString::fromStdString("Objednať\n(" + std::to_string(totalOrder) + ")"));
    else
        order->setText("Objednať");
}

void FoodWindow::plusClicked()
{
    totalOrder++;
    order->setText(QString::fromStdString("Objednať\n(" + std::to_string(totalOrder) + ")"));
}
