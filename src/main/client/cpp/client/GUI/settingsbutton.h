#ifndef SETTINGSBUTTON_H
#define SETTINGSBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class SettingsButton : public QWidget
{
    Q_OBJECT
public:
    SettingsButton(QWidget *);
    ~SettingsButton();

private:
    QPushButton *label;

    void paintEvent(QPaintEvent *);

private slots:
    void openSettings();

signals:
    void openSettings_s();
};

#endif // SETTINGSBUTTON_H
