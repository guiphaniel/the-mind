CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=thread
CONFIG += link_pkgconfig
CONFIG += debug
PKGCONFIG += protobuf
LIBS+=-pthread


INCLUDEPATH += libs/socket/
INCLUDEPATH += src/protos/
INCLUDEPATH += src/client/
INCLUDEPATH += src/room/

HEADERS += \
    libs/socket/socket.h \
    src/client/client.h \
    src/room/room.h \
    src/protos/player.pb.h \
    src/protos/room.pb.h \
    src/protos/rooms_list.pb.h \
    src/protos/card.pb.h \
    src/protos/cards_list.pb.h \
    src/protos/player_cards_map.pb.h \

SOURCES += \
    libs/socket/socket.cpp \
    src/server.cpp \
    src/client/client.cpp \
    src/room/room.cpp \
    src/protos/player.pb.cc \
    src/protos/room.pb.cc \
    src/protos/rooms_list.pb.cc \
    src/protos/card.pb.cc \
    src/protos/cards_list.pb.cc \
    src/protos/player_cards_map.pb.cc \
