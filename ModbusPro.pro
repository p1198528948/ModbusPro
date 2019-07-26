#-------------------------------------------------
#
# Project created by QtCreator 2019-07-25T09:10:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# qt log
include (./src/QsLog.pri)

TARGET = ModbusPro
TEMPLATE = app
VERSION = 1.0.0

win32: DEFINES += _WIN32
unix:!macx: DEFINES += _LINUX_

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    3rdparty/qextserialport/qextserialport.cpp	\
    3rdparty/libmodbus/src/modbus.c \
    3rdparty/libmodbus/src/modbus-data.c \
    3rdparty/libmodbus/src/modbus-rtu.c \
    3rdparty/libmodbus/src/modbus-tcp.c \
    3rdparty/libmodbus/src/modbus-ascii.c \
    document.cpp

HEADERS += \
        mainwindow.h \
    3rdparty/qextserialport/qextserialport.h \
    3rdparty/qextserialport/qextserialenumerator.h \
    3rdparty/libmodbus/src/modbus.h \
    document.h \
    user.h

FORMS += \
        mainwindow.ui

win32 {
    SOURCES += 3rdparty/qextserialport/win_qextserialport.cpp \
           3rdparty/qextserialport/qextserialenumerator_win.cpp
    DEFINES += _TTY_WIN_  WINVER=0x0501
    LIBS += -lsetupapi -lws2_32
}

unix {
    SOURCES += 3rdparty/qextserialport/posix_qextserialport.cpp	\
           3rdparty/qextserialport/qextserialenumerator_unix.cpp
    DEFINES += _TTY_POSIX_
}

INCLUDEPATH += 3rdparty/libmodbus \
               3rdparty/libmodbus/src \
               3rdparty/qextserialport \
               src

CONFIG += C++11
