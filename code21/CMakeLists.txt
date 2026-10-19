# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave attack.c damage.c expand.c inventory.c inventory2.c location.c main.c match.c misc.c move.c noun.c object.c onoff.c openclose.c parsexec.c reach.c social.c talk.c toggle.c turn.c)

install(TARGETS lilcave)
