# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave attack.c break.c client.c damage.c expand.c inventory.c inventory2.c location.c main.c match.c misc.c move.c noun.c object.c onoff.c openclose.c outbuf.c parsexec.c print.c reach.c server.c social.c talk.c tcp.c telnet.c toggle.c turn.c)

install(TARGETS lilcave)
