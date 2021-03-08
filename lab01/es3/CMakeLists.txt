cmake_minimum_required(VERSION 3.6)
project(lab1_3)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(lab1_3 ${SOURCE_FILES})