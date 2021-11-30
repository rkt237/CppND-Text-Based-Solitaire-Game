cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-std=c++17)

set(CURSES_NEED_NCURSES TRUE)

set(CXX_FLAGS "-Wall")
set(CXX_FLAGS "-lncurses")
set(CXX_FLAGS "-lncursesw")
set(CXX_FLAGS "-ltinfo")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set( CMAKE_INCLUDE_PATH "/usr/include")
set( CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/libncurses.so")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#set(DCURSES_LIBRARY "/usr/include")

project(Solitaire)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES   src/main.cpp
                    src/card.cpp 
                    src/pile.cpp 
                    src/deskpile.cpp
                    src/discardpile.cpp
                    src/suitpile.cpp 
                    src/tablepile.cpp 
                    src/controller.cpp 
                    src/renderer.cpp 
                    src/game.cpp
                     )

add_executable(Solitaire ${SOURCES})

string(STRIP ${CURSES_LIBRARIES} CURSES_LIBRARIES)

set_property(TARGET Solitaire PROPERTY CXX_STANDARD 17)
target_link_libraries(Solitaire ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(Solitaire PRIVATE -Wall -Wextra)