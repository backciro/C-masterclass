cmake_minimum_required(VERSION 3.6)
project(clion)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c esercizio.c categoria.c)
add_executable(clion ${SOURCE_FILES})