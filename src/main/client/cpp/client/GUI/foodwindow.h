#ifndef FOODWINDOW_H
#define FOODWINDOW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <vector>

class FoodWindow : public QWidget
{
    Q_OBJECT
public:
    FoodWindow(QWidget *, long);
    ~FoodWindow();

private:
    long facilityID;
    QScrollArea *scrollArea;
    QGridLayout *layout;
    QWidget *tabs;
    std::vector<QWidget *> foodTabs;

signals:
    // for changing name of window
    void changeName_s(QString);

public slots:
    void sizeChanged(QSize);
    void updateFacility(long);
};

#endif // FOODWINDOW_H
