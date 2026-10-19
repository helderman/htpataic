# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave expand.c inventory.c inventory2.c location.c main.c match.c misc.c move.c noun.c object.c onoff.c openclose.c parsexec.c reach.c toggle.c)

install(TARGETS lilcave)
