#-------------------------------------------------
#
# Project created by QtCreator 2021-12-10T16:48:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    extra.cpp \
    node.cpp \
    xml_tree.cpp

HEADERS  += mainwindow.h \
    extra.h \
    node.h \
    xml_tree.h

FORMS    += mainwindow.ui
