#-------------------------------------------------
#
# Project created by QtCreator 2021-08-29T16:40:19
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Task-Manager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    server.h \
    thread.h

FORMS    += mainwindow.ui
