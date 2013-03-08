#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T15:57:54
#
#-------------------------------------------------

QT       += core gui
QT	     += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Linpop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    chatroom.cpp \
    Packet.cpp \
    dataBuilder.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    client.h \
    chatroom.h \
    Packet.hh \
    dataBuilder.hh \
    user.hh

FORMS    += mainwindow.ui \
    chatroom.ui
