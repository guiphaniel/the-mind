CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=thread
CONFIG += link_pkgconfig
PKGCONFIG += protobuf
LIBS+=-pthread


INCLUDEPATH += libs/socket/
INCLUDEPATH += src/protos/
INCLUDEPATH += src/client/

HEADERS += \
    libs/socket/socket.h \
    src/client/client.h \
    src/protos/player.pb.h \
    src/protos/room.pb.h \

SOURCES += \
    libs/socket/socket.cpp \
    src/server.cpp \
    src/client/client.cpp \
    src/protos/player.pb.cc \
    src/protos/room.pb.cc \
