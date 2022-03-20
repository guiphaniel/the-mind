CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=thread
LIBS+=-pthread

INCLUDEPATH += libs/socket/
INCLUDEPATH += src/protos/
INCLUDEPATH += src/client/

HEADERS += \
    libs/socket/socket.h \
    src/client/client.h \

SOURCES += \
    libs/socket/socket.cpp \
    src/server.cpp \
    src/client/client.cpp \
