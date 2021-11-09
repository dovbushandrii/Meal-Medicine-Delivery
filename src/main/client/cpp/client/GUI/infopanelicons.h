/**
 * @file infopanelicons.h
 * @author Rastislav Budinsky
 * @brief This file contains InfoPanelIcons, which hides widgets behind buttons
 */
#ifndef INFOPANELICONS_H
#define INFOPANELICONS_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class InfoPanelIcons : public QWidget
{
    Q_OBJECT
public:
    InfoPanelIcons(QWidget *);
    ~InfoPanelIcons();

private:
    QPushButton *settings;
    QPushButton *profile;

signals:
    void openSettings_s();
    void switchContent_s();

public slots:
    void openSettings();
    void openInfoPanel();
};

#endif // INFOPANELICONS_H
