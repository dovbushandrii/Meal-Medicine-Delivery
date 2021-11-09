#include "personaldata.h"
#include "mainwindow.h"
#include "infopanel.h"

#include "../model/daos/ClientDAO.h"

PersonalData::PersonalData(QWidget *parent) : QWidget(parent)
{
    // height is sum of all elements here
    setFixedSize(INFO_PANEL_WIDTH, 3 * TITLE_HEIGHT);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    name = new QLabel(QString::fromStdString("Meno: " + client.getName() + "\nPriezvisko: " + client.getSurname()), this);
    name->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT);
    name->setStyleSheet("* {qproperty-alignment: AlignLeft; font-size: 12pt;background-color: rgba(0,0,0,0);}");

    phoneNumber = new QLabel(QString::fromStdString("Tel. číslo: " + client.getPhoneNumber()), this);
    phoneNumber->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT / 2);
    phoneNumber->setStyleSheet("* {qproperty-alignment: AlignLeft; font-size: 12pt;background-color: rgba(0,0,0,0);}");

    email = new QLabel(QString::fromStdString("Email: " + client.getEmail()), this);
    email->setFixedSize(INFO_PANEL_WIDTH, TITLE_HEIGHT / 2);
    email->setStyleSheet("* {qproperty-alignment: AlignLeft; font-size: 12pt;background-color: rgba(0,0,0,0);}");

    layout = new QVBoxLayout(this);
    layout->addWidget(name);
    layout->addWidget(phoneNumber);
    layout->addWidget(email);
}

PersonalData::~PersonalData()
{

}

void PersonalData::updateClientData(long id)
{
    ClientDAO clientDAO;
    client = clientDAO.readClient(id);
    name->setText(QString::fromStdString("Meno: " + client.getName() + "\nPriezvisko: " + client.getSurname()));
    phoneNumber->setText(QString::fromStdString("Tel. číslo: " + client.getPhoneNumber()));
    email->setText(QString::fromStdString("Email: " + client.getEmail()));
}
