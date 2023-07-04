#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "../../include/Grid/grid.h"

void Grid::randomizeCells(int pctRandom) {
    int max = 100;
    int min = 1;
    int randNum = 0;

    // Update Actual grid
    for (auto& row : this->m_grid) {
        for (auto cell : row) {
            randNum = std::rand() % (max-min + 1) + min;
            if (randNum <= pctRandom) {
                cell = true;
            }
        }
    }

    std::cout << "Welp I got here" << std::endl;

    this->updateDisplayGrid();
}

const BooleanGrid Grid::getDisplayGrid() {
    return this->m_displayGrid;
}

void Grid::moveDisplayX(int value) {
    int min = 0;
    int max = (int)this->m_grid[0].size() - (int)this->m_displayGrid[0].size();
    this->m_displayX = std::max(0, std::min(this->m_displayX + value, max));
    std::cout << "After: " << this->m_displayX << std::endl;
    this->updateDisplayGrid();
}

void Grid::moveDisplayY(int value) {
    std::cout << "initial: " << this->m_displayY << std::endl;
    int min = 0;
    int max = (int)this->m_grid.size() - (int)this->m_displayGrid.size();
    this->m_displayY = std::max(min, std::min(this->m_displayY + value, max));
    std::cout << "After: " << this->m_displayY << std::endl;
    this->updateDisplayGrid();
}

void Grid::updateDisplayGrid() {
    for (int i = 0; i < this->m_displayGrid.size(); i++) {
        const std::vector<bool> &gridRow = this->m_grid[this->m_displayY + i];
        for (int j = 0; j < this->m_displayGrid[0].size(); j++) {
            this->m_displayGrid[i][j] = gridRow[this->m_displayX + j];
        }
    }
}