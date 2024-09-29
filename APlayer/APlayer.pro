# Project Configuration
QT += core gui webenginewidgets

# Target
TARGET = APlayer
TEMPLATE = app

# Source and Header Files
SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h


FORMS += mainwindow.ui

# Include Paths
INCLUDEPATH += .

# Compiler Settings
CONFIG += c++11
