#include "foodwindow.h"
#include "foodtab.h"
#include "infopanel.h"
#include "mainwindow.h"

#include "../model/daos/MealDAO.h"
#include "../model/entities/Meal.h"

#include <cmath>

#define DEFAULT_SPACE 25

FoodWindow::FoodWindow(QWidget *parent, long facilityID) : QWidget(parent)
{
    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    setFixedSize(TAB_WIDTH + TITLE_WIDTH, TAB_HEIGHT + TITLE_HEIGHT);

    tabs = new QWidget(this);
    tabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("* {border: 0px; background: transparent;}");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(tabs);

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

void FoodWindow::sizeChanged(QSize size)
{
    for (auto widget : foodTabs)
        layout->removeWidget(widget);

    setFixedSize(size.width() - (TITLE_WIDTH + INFO_PANEL_WIDTH), size.height() - 2 * TITLE_HEIGHT);
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
    // update this
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
