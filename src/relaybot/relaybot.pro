QT += core
QT -= gui

CONFIG += c++11

TARGET = relaybot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    relaybot.cpp

HEADERS += \
    relaybot.h
