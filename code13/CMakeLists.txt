# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave inventory.c location.c main.c match.c misc.c move.c noun.c object.c openclose.c parsexec.c reach.c toggle.c)

install(TARGETS lilcave)
