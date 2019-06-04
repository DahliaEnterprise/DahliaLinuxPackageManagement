TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dependency.cpp \
    entiredependencylist.cpp

HEADERS += \
    dependency.h \
    entiredependencylist.h

DISTFILES += \
    main.cpp.DEPRECATED
