/**
 * @file title.cpp
 * @author Rastislav Budinsky
 * @brief This file contains implementation of class Title
 */
#include "title.h"

#include "mainwindow.h"

Title::Title(QWidget *parent, QApplication *app) : QWidget(parent)
{
    titleBar = new TitleBar(this, app);
    returnBar = new ReturnBar(this);
    movingBar = new MovingBar(this);
    name_label = new QLabel(this);

    name_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name_label->setContentsMargins(50, 0, 0, 0);
    name_label->setStyleSheet("QLabel{color: black; background: transparent; font: bold 'Arial Black'; font-size:21pt}");

    QObject::connect(parent, SIGNAL(sizeChangedTitle_s(QSize)), movingBar, SLOT(changeWidth(QSize)));
    QObject::connect(parent, SIGNAL(toggleDescription_s()), movingBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(moveWindow_s(QPair<int, int>)), parent, SLOT(moveWindow(QPair<int, int>)));

    QObject::connect(parent, SIGNAL(toggleDescription_s()), titleBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(showMinimized_s()), parent, SLOT(showMinimized()));
    QObject::connect(this, SIGNAL(fullScreen_s()), parent, SLOT(fullScreen()));

    QObject::connect(parent, SIGNAL(toggleDescription_s()), returnBar, SLOT(toggleDescription()));
    QObject::connect(this, SIGNAL(stepBack_s()), parent, SLOT(stepBack()));

    QObject::connect(parent, SIGNAL(changeName_s(QString)), this, SLOT(changeName(QString)));
    QObject::connect(parent, SIGNAL(sizeChangedTitle_s(QSize)), this, SLOT(sizeChangedTitle(QSize)));

    QHBoxLayout *layoutTitle = new QHBoxLayout(this);
    QHBoxLayout *layoutTitleBar = new QHBoxLayout();
    QHBoxLayout *layoutReturnBar = new QHBoxLayout();

    layoutTitle->setContentsMargins(0, 0, 0, 0);
    layoutTitle->setSpacing(0);
    layoutTitleBar->setContentsMargins(0, 0, 0, 0);
    layoutTitleBar->setSpacing(0);
    layoutReturnBar->setContentsMargins(0, 0, 0, 0);
    layoutReturnBar->setSpacing(0);

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
}

Title::~Title()
{

}

void Title::changeName(QString new_name)
{
    name_label->setText(new_name);
}

void Title::sizeChangedTitle(QSize size)
{
    name_label->setFixedSize((size.width() - 4 * TITLE_WIDTH) / 2, TITLE_HEIGHT);
}

void Title::showMinimized()
{
    emit showMinimized_s();
}

void Title::fullScreen()
{
    emit fullScreen_s();
}

void Title::moveWindow(QPair<int, int> new_pos)
{
    emit moveWindow_s(new_pos);
}

void Title::stepBack()
{
    emit stepBack_s();
}
