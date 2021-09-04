TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    item.cpp \
    itemImpl.cpp \
    main.cpp \
    netHolder.cpp \
    strategy.cpp

HEADERS += \
    item.h \
    itemImpl.h \
    logwrite.h \
    netHolder.h \
    singleton.h \
    strategy.h \
    types.h
