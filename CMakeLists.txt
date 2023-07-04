cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

# Add your source files to the project
set(SOURCES
    src/main.cpp
    src/Grid/grid.cpp
    src/Simulation/simulation.cpp
    # Add more source files as needed
)

# Set the target executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Find the ncurses library
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED Paths /usr/include/ncurses.h)
target_include_directories(GameOfLife PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(GameOfLife ${CURSES_LIBRARIES})