TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dependency.cpp \
    manifestlist.cpp

HEADERS += \
    dependency.h \
    manifestlist.h
