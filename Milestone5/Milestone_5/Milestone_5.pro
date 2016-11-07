#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T13:18:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Milestone_5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rs232.c \
    bmp_file.cpp

HEADERS  += mainwindow.h \
    rs232.h \
    bmp_file.h

FORMS    += mainwindow.ui
