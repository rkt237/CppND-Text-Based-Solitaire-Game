cmake_minimum_required(VERSION 2.6)

# set the project name and version
project(curseSoli)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(Solitaire ${SOURCES})

# add the executable
#add_executable (Solitaire src/main.cpp src/card.cpp src/pile.cpp src/deskpile.cpp src/discardpile.cpp src/suitpile.cpp src/tablepile.cpp src/controller.cpp src/renderer.cpp src/game.cpp )

set_property(TARGET Solitaire PROPERTY CXX_STANDARD 17)
target_link_libraries(Solitaire ${CURSES_LIBRARIES})

#target_compile_options(Solitaire PRIVATE -DUNICODE -Wall -lncurses -ltinfo)
target_compile_options(Solitaire PRIVATE -Wall -Wextra)