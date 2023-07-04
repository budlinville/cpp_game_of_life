#pragma once

#include "../Grid/grid.h"

class Simulation {
public:
    Simulation(int size, int displaySize, int pctAlive)
        : m_grid(Grid(500, 50, 30))
        {
            this->init();
        }
    
    Simulation(Grid grid)
        : m_grid(grid)
        {
            this->init();
        }
    
    ~Simulation();

    void run();

private:
    Grid m_grid;

    void init();
    void displayGrid();
    bool handleKeyPress(int key);
};
