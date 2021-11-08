#include "waitingscreen.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMovie>
#include <QStyleOption>
#include <QPainter>

WaitingScreen::WaitingScreen(QWidget *parent, QString description) : QWidget(parent)
{
    setStyleSheet(".OrderWaiting{background: black;}");

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet(".QWidget{background-color: transparent;}");

    QObject::connect(parent, SIGNAL(sizeChanged_s(QSize)), this, SLOT(sizeChanged(QSize)));
    QObject::connect(this, SIGNAL(changeName_s(QString)), parent, SLOT(changeName(QString)));
    QObject::connect(this, SIGNAL(finishedWaiting_s()), parent, SLOT(finishedWaiting()));
    QObject::connect(parent, SIGNAL(start_s()), this, SLOT(start()));

    QVBoxLayout *layout = new QVBoxLayout(mainWidget);
    layout->setAlignment(Qt::AlignHCenter);

    QLabel *label = new QLabel(description, mainWidget);
    label->setStyleSheet("QLabel{qproperty-alignment: AlignCenter; font-size: 30px}");

    QLabel *loader = new QLabel(mainWidget);
    QMovie *movie = new QMovie("../imgs/loader.gif");
    loader->setMovie(movie);
    movie->start();

    layout->addWidget(loader);
    layout->addWidget(label);

    emit changeName_s("Načítavanie");
}

WaitingScreen::~WaitingScreen()
{

}

void WaitingScreen::start()
{

}

void WaitingScreen::sizeChanged(QSize size)
{
    size.setWidth(size.width());
    setFixedSize(size);
    mainWidget->setFixedSize(size);
}

void WaitingScreen::paintEvent(QPaintEvent *)
{
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
