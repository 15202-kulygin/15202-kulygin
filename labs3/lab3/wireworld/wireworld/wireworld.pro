#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T19:23:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wireworld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    field.h \
    widget.h

FORMS    += mainwindow.ui \
    widget.ui
