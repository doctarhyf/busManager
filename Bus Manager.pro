#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T16:26:38
#
#-------------------------------------------------

QT       += core gui network xml sql multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BusManager
TEMPLATE = app
ICON = tkt_logo.icns



SOURCES += main.cpp \
    formlogin.cpp \
    mainwindowadmin.cpp \
    dialogaddbus.cpp \
    dbmanager.cpp \
    mainwindowticketer.cpp \
    dialogaddstation.cpp \
    dialogaddroute.cpp \
    dialogaddticketer.cpp \
    formticketsells.cpp \
    formwholeticketsells.cpp \
    dialogaddbustotimetable.cpp \
    dialogadddriver.cpp \
    mainwindowticketer2.cpp \
    dialogpersonalreport.cpp

HEADERS  += \
    formlogin.h \
    mainwindowadmin.h \
    dialogaddbus.h \
    dbmanager.h \
    mainwindowticketer.h \
    dialogaddstation.h \
    dialogaddroute.h \
    dialogaddticketer.h \
    formticketsells.h \
    formwholeticketsells.h \
    root.h \
    dialogaddbustotimetable.h \
    dialogadddriver.h \
    mainwindowticketer2.h \
    dialogpersonalreport.h

FORMS    += \
    formlogin.ui \
    mainwindowadmin.ui \
    dialogaddbus.ui \
    mainwindowticketer.ui \
    dialogaddstation.ui \
    dialogaddroute.ui \
    dialogaddticketer.ui \
    formticketsells.ui \
    formwholeticketsells.ui \
    dialogaddbustotimetable.ui \
    dialogadddriver.ui \
    mainwindowticketer2.ui \
    dialogpersonalreport.ui

RESOURCES += \
    res.qrc
