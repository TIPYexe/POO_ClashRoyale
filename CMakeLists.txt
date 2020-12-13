cmake_minimum_required(VERSION 3.15)
project(ConsoleApplication1)

set(CMAKE_CXX_STANDARD 17)


include_directories(.)

add_executable(ConsoleApplication1
        ConsoleApplication1.cpp
        Harta.cpp
        Harta.h
        Header.h
        Personaj.cpp
        Personaj.h
        Side.h
        Turn.cpp
        Turn.h)
target_link_libraries(ConsoleApplication1)