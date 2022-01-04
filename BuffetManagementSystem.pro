#-------------------------------------------------
#
# Project created by QtCreator 2020-08-12T09:23:06
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BuffetManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    adminwindow.cpp \
    goble.cpp \
    LoginWindow.cpp \
    main.cpp \
    payform.cpp \
    WorkerWindow.cpp



HEADERS += \
    AdminWindow.h \
    goble.h \
    LoginWindow.h \
    mysqlcon.h \
    payform.h \
    WorkerWindow.h



FORMS += \
    AdminWindow.ui \
    LoginWindow.ui \
    payform.ui \
    WorkerWindow.ui


RESOURCES += \
    resources.qrc

DISTFILES += \
    qss/black.css \
    qss/blue.css \
    qss/brown.css \
    qss/darkgray.css \
    qss/dev.css \
    qss/gray.css \
    qss/lightgray.css \
    qss/silvery.css
