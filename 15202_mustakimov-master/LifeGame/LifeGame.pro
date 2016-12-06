#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T09:01:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LifeGame
TEMPLATE = app


SOURCES += main.cpp\
    field.cpp \
    fieldwidget.cpp \
    mainwindow.cpp \
    resizefielddialog.cpp

HEADERS  += \
    field.h \
    fieldwidget.h \
    mainwindow.h \
    resizefielddialog.h

FORMS    += \
    mainwindow.ui \
    resizefielddialog.ui
