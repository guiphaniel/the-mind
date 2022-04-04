#! /bin/sh

protoc -I=. --cpp_out=. player.proto
protoc -I=. --cpp_out=. room.proto
protoc -I=. --cpp_out=. rooms_list.proto
protoc -I=. --cpp_out=. card.proto
protoc -I=. --cpp_out=. cards_list.proto