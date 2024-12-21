cmake_minimum_required(VERSION 3.22.1)
project(REP_EDITOR)


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
find_package(nlohmann_json REQUIRED)
find_package(Curses REQUIRED)
find_package(tree-sitter REQUIRED)
# Source files for your project
set(SOURCES
		${CMAKE_SOURCE_DIR}/src/Syntax.cpp
		${CMAKE_SOURCE_DIR}/src/Editor.cpp
		${CMAKE_SOURCE_DIR}/src/Screen.cpp
		${CMAKE_SOURCE_DIR}/src/NormalMode.cpp
		${CMAKE_SOURCE_DIR}/src/InsertMode.cpp
		${CMAKE_SOURCE_DIR}/src/Highlight.cpp
		${CMAKE_SOURCE_DIR}/src/File.cpp
		${CMAKE_SOURCE_DIR}/src/ClipBoard.cpp
		${CMAKE_SOURCE_DIR}/src/ColorScheme.cpp
		${CMAKE_SOURCE_DIR}/rep.cpp
# Replace with your actual source files
)
add_executable(REP ${SOURCES})

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build")

target_link_libraries(REP PRIVATE
    nlohmann_json::nlohmann_json
    ${CURSES_LIBRARIES}
    tree-sitter::tree-sitter
)

target_link_libraries(REP PRIVATE dl)


# Install rules (optional)
install(TARGETS REP RUNTIME DESTINATION bin)
