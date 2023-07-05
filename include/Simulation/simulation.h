#pragma once

#include <mutex>

#include "../Grid/grid.h"

class Simulation {
public:    
    Simulation(Grid grid)
        : m_grid(grid)
        {
            this->init();
        }

    Simulation(int size, int pctAlive);
    
    ~Simulation();

    void run();

private:
    Grid m_grid;
    int m_terminalWidth;
    int m_terminalHeight;
    std::mutex m_gridMtx;  // Mutex for synchronizing access to m_grid
    int m_pctAlive;

    void init();
    void displayGrid();
    bool handleKeyPress(int key);

    void updateGridThread();
};
