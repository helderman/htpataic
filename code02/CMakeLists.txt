# Build script for CMake

cmake_minimum_required(VERSION 3.14)

project(LittleCave DESCRIPTION "Little Cave Adventure")

add_executable(lilcave main.c parsexec.c)

install(TARGETS lilcave)
