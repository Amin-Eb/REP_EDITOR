cmake_minimum_required(VERSION 3.22.1)
project(REP_EDITOR)
set(CMAKE_CXX_STANDARD 20)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(REP rep.cpp)
target_link_libraries(REP ${CURSES_LIBRARIES})
