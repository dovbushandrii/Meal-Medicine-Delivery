QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/daos/ClientJSONSerializer.cpp \
    ../model/daos/FacilityJSONSerializer.cpp \
    ../model/daos/MealJSONSerializer.cpp \
    ../model/daos/MedicineJSONSerializer.cpp \
    ../model/daos/OrderJSONSerializer.cpp \
    infopanel.cpp \
    infopanelicons.cpp \
    itemtab.cpp \
    itemwindow.cpp \
    loginscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    movingbar.cpp \
    nextmeal.cpp \
    orderpreview.cpp \
    orderpreviewwindow.cpp \
    ordertab.cpp \
    orderwindow.cpp \
    personaldata.cpp \
    popup.cpp \
    returnbar.cpp \
    settings.cpp \
    settingsbutton.cpp \
    title.cpp \
    titlebar.cpp \
    waitingscreen.cpp \
    welcomewindow.cpp

HEADERS += \
    ../model/daos/ClientDAO.h \
    ../model/daos/ClientJSONSerializer.h \
    ../model/daos/FacilityDAO.h \
    ../model/daos/FacilityJSONSerializer.h \
    ../model/daos/HTTPMethod.h \
    ../model/daos/HTTPRequest.h \
    ../model/daos/HTTPResponse.h \
    ../model/daos/HTTPSender.h \
    ../model/daos/MealDAO.h \
    ../model/daos/MealJSONSerializer.h \
    ../model/daos/MedicineDAO.h \
    ../model/daos/MedicineJSONSerializer.h \
    ../model/daos/OrderDAO.h \
    ../model/daos/OrderJSONSerializer.h \
    ../model/daos/ServerURLs.h \
    ../model/entities/Allergen.h \
    ../model/entities/Client.h \
    ../model/entities/Facility.h \
    ../model/entities/Meal.h \
    ../model/entities/Medicine.h \
    ../model/entities/Order.h \
    ../model/entities/PendingOrder.h \
    infopanel.h \
    infopanelicons.h \
    itemtab.h \
    itemwindow.h \
    loginscreen.h \
    mainwindow.h \
    menu.h \
    movingbar.h \
    nextmeal.h \
    orderpreview.h \
    orderpreviewwindow.h \
    ordertab.h \
    orderwindow.h \
    personaldata.h \
    popup.h \
    returnbar.h \
    settings.h \
    settingsbutton.h \
    title.h \
    titlebar.h \
    waitingscreen.h \
    welcomewindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    GUI_cs_CZ.ts
CONFIG += lrelease
CONFIG += embed_translations

INCLUDEPATH += connect/json/include
LIBS += -LD:\Qt\5.12.12\mingw73_64\lib -lcurl

DEFINES += CURL_STATICLIB

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



