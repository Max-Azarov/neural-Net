TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    item.cpp \
    itemImpl.cpp \
    main.cpp

HEADERS += \
    item.h \
    itemImpl.h \
    logwrite.h \
    singleton.h
