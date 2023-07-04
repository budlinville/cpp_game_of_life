#include <ncurses.h>

#include "../../include/Simulation/simulation.h"

Simulation::~Simulation() {
    // End ncurses
    endwin();
}

void Simulation::run() {
    while (true) {
        // Display the entire grid
        this->displayGrid();

        // Wait for user input
        int key = getch();
        if (!handleKeyPress(key)) {
            break;
        }

        printw("start X: " + this->m_grid.m_displayX);
        printw("start Y: " + this->m_grid.m_displayY);
    }
}

void Simulation::init() {
    initscr();
    keypad(stdscr, TRUE); // Enable special key handling
    noecho(); // Do not echo user input
}

void Simulation::displayGrid() {
    // Clear the screen
    clear();


    // Iterate over the grid and print the entire grid
    for (const auto& row : this->m_grid.getDisplayGrid()) {
        for (const auto& cell : row) {
            printw(cell ? "O" : " ");
        }
        printw("\n");
    }

    // Refresh the screen to display the changes
    refresh();
}

// Returns true if simulation should keep going
bool Simulation::handleKeyPress(int key) {
    switch (key) {
        case KEY_UP:
            this->m_grid.moveDisplayY(-1);
            break;
        case KEY_DOWN:
            this->m_grid.moveDisplayY(1);
            break;
        case KEY_LEFT:
            this->m_grid.moveDisplayX(-1);
            break;
        case KEY_RIGHT:
            this->m_grid.moveDisplayX(1);
            break;
        case 27:
            return false;
        default:
            // Handle other keys if needed
            break;
    }

    return true;
}