QT += core gui
CONFIG += console c++17

# Agrega la carpeta headers a la ruta de inclusión
INCLUDEPATH += $$PWD/headers

SOURCES += main.cpp \
    bitops.cpp

HEADERS += \
    headers/bitops.h
