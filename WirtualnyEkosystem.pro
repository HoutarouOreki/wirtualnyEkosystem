TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bakteria.cpp \
        funkcjeUtility.cpp \
        glon.cpp \
        grzyb.cpp \
        main.cpp \
        organizm.cpp \
        srodowisko.cpp

HEADERS += \
    bakteria.h \
    funkcjeUtility.h \
    glon.h \
    grzyb.h \
    organizm.h \
    srodowisko.h
    
LIBS += \
    -L/usr/lib -lncurses
