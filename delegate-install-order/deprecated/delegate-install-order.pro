TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dependency.cpp \
    entiredependencylist.cpp \
    installorderqueue.cpp \
    installorderqueuegenerator.cpp

HEADERS += \
    dependency.h \
    entiredependencylist.h \
    installorderqueue.h \
    installorderqueuegenerator.h

DISTFILES += \
    main.cpp.DEPRECATED
