QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    foodtab.cpp \
    foodwindow.cpp \
    infopanel.cpp \
    main.cpp \
    mainwindow.cpp \
    movingbar.cpp \
    nextmeal.cpp \
    ordertab.cpp \
    orderwindow.cpp \
    personaldata.cpp \
    returnbar.cpp \
    settings.cpp \
    settingsbutton.cpp \
    title.cpp \
    titlebar.cpp \
    welcomewindow.cpp

HEADERS += \
    foodtab.h \
    foodwindow.h \
    infopanel.h \
    mainwindow.h \
    movingbar.h \
    nextmeal.h \
    ordertab.h \
    orderwindow.h \
    personaldata.h \
    returnbar.h \
    settings.h \
    settingsbutton.h \
    title.h \
    titlebar.h \
    welcomewindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    GUI_cs_CZ.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
