# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave location.c main.c misc.c noun.c object.c parsexec.c)

install(TARGETS lilcave)
