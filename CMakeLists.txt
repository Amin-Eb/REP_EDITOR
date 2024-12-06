cmake_minimum_required(VERSION 3.22.1)
project(CUR)
set(CMAKE_CXX_STANDARD 20)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


