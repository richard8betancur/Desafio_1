QT += core gui
CONFIG += console c++17

INCLUDEPATH += $$PWD/headers

SOURCES += main.cpp \
    Launcher.cpp \
    Verificador.cpp \
    bitops.cpp

HEADERS += \
    headers/bitops.h
