cmake_minimum_required(VERSION 3.22.1)
project(REP_EDITOR)


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Source files for your project
set(SOURCES
		${CMAKE_SOURCE_DIR}/src/json.hpp
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

# Add Tree-sitter sources
set(TREESITTER_SOURCES
    ${CMAKE_SOURCE_DIR}/tree-sitter/lib/src/lib.c  # Tree-sitter core library
)

# Add Tree-sitter grammar sources (e.g., C language grammar)
set(TREESITTER_GRAMMAR_SOURCES
    ${CMAKE_SOURCE_DIR}/tree-sitter-cpp/src/parser.c
    ${CMAKE_SOURCE_DIR}/tree-sitter-cpp/src/scanner.c
)

# Combine all sources
list(APPEND SOURCES ${TREESITTER_SOURCES} ${TREESITTER_GRAMMAR_SOURCES})

# Include directories for Tree-sitter
include_directories(
    ${CMAKE_SOURCE_DIR}/tree-sitter/lib/include
    ${CMAKE_SOURCE_DIR}/tree-sitter/lib/src
    ${CMAKE_SOURCE_DIR}/tree-sitter-c/src  # Adjust for grammars
)

# Add executable target
add_executable(REP ${SOURCES})

# Link ncurses
find_package(Curses REQUIRED)
target_link_libraries(REP PRIVATE ${CURSES_LIBRARIES})

# Link dl library (for dynamic linking if needed)
target_link_libraries(REP PRIVATE dl)

# Optional: Add compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(REP PRIVATE -lncurces -ltree-sitter -ldl)
endif()

# Install rules (optional)
install(TARGETS REP RUNTIME DESTINATION bin)
