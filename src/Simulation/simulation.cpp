#include <ncurses.h>
#include <chrono>
#include <thread>

#include "../../include/Simulation/simulation.h"

Simulation::Simulation(int size, int pctAlive) {
    this->init();
    m_grid = Grid(size, this->m_terminalWidth, this->m_terminalHeight, pctAlive);
}

Simulation::~Simulation() {
    // End ncurses
    endwin();
}

void Simulation::run() {
    std::thread t(&Simulation::updateGridThread, this);

    while (true) {
        // Display the entire grid
        this->displayGrid();

        // Wait for user input
        int key = getch();
        if (!handleKeyPress(key)) {
            break;
        }
    }

    t.join();
}

void Simulation::init() {
    initscr();
    keypad(stdscr, TRUE);   // Enable special key handling
    noecho();               // Do not echo user input
    getmaxyx(stdscr, this->m_terminalHeight, this->m_terminalWidth);
}

void Simulation::displayGrid() {
    // Clear the screen
    clear();

    // Iterate over the grid and print the entire grid
    for (const auto& row : this->m_grid.getDisplayGrid()) {
        for (const auto& cell : row) {
            printw(cell ? "O" : " ");
        }
        // printw("\n");  // Don't need this anymore because we fit exactly as many characters as needed, so newline is triggered automatically
    }

    // Refresh the screen to display the changes
    refresh();
}

// Returns true if simulation should keep going
bool Simulation::handleKeyPress(int key) {
    std::lock_guard<std::mutex> lock(this->m_gridMtx);
    switch (key) {
        case KEY_UP:
            this->m_grid.moveDisplayY(-2);
            break;
        case KEY_DOWN:
            this->m_grid.moveDisplayY(2);
            break;
        case KEY_LEFT:
            this->m_grid.moveDisplayX(-2);
            break;
        case KEY_RIGHT:
            this->m_grid.moveDisplayX(2);
            break;
        case 27:
            return false;
        default:
            // Handle other keys if needed
            break;
    }

    return true;
}

void Simulation::updateGridThread() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(this->m_gridMtx);  // Acquire the lock
            this->m_grid.incrementGrid();
            this->displayGrid();
        }  // Lock released here

        // Sleep for specified duration
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Example sleep duration
    }
}