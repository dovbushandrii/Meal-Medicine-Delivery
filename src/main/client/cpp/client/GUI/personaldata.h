/**
 * @file personaldata.h
 * @author Rastislav Budinsky
 * @brief This file contains class PersonalData, which displays personal data of the current user
 */
#ifndef PERSONALDATA_H
#define PERSONALDATA_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include "../model/entities/Client.h"

#include <QVBoxLayout>

class PersonalData : public QWidget
{
    Q_OBJECT
public:
    PersonalData(QWidget *);
    ~PersonalData();

private:
    QLabel *name;
    QLabel *email;
    QLabel *phoneNumber;
    Client client;

    QVBoxLayout *layout;

public slots:
    void updateClientData(long);
};

#endif // PERSONALDATA_H
