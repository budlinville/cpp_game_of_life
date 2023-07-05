#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <thread>

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
    this->updateDisplayGrid();
}

void Grid::moveDisplayY(int value) {
    int min = 0;
    int max = (int)this->m_grid.size() - (int)this->m_displayGrid.size();
    this->m_displayY = std::max(min, std::min(this->m_displayY + value, max));
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

void Grid::incrementGrid() {
    Grid newGrid = *this;

    for (int i = 0; i < this->m_grid.size(); i++ ) {
        for (int j = 0; j < this->m_grid[0].size(); j++) {
            int aliveNeighbors = this->getSurroundingAliveCells(i, j);
            newGrid.m_grid[j][i] = (this->m_grid[j][i])
                ? (aliveNeighbors == 2 || aliveNeighbors == 3)  // Alive
                : (aliveNeighbors == 3);                        // Dead
        }
    }

    this->m_grid = newGrid.m_grid;
    this->updateDisplayGrid();
}

int Grid::getSurroundingAliveCells(int x, int y) {
    int count = 0;
    int numRows = this->m_grid.size();
    int numCols = this->m_grid[0].size();

    // Check the eight surrounding cells
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Skip the current cell itself
            if (i == 0 && j == 0) continue;

            int neighborX = x + i;
            int neighborY = y + j;

            // Handle the edges of the screen
            neighborX = (neighborX < 0)         ? numCols - 1   : neighborX;  // Wrap around to the rightmost column
            neighborX = (neighborX >= numCols)  ? 0             : neighborX;  // Wrap around to the leftmost column
            neighborY = (neighborY < 0)         ? numRows - 1   : neighborY;  // Wrap around to the bottom row
            neighborY = (neighborY >= numRows)  ? 0             : neighborY;  // Wrap around to the top row

            // Check the state of the neighbor cell
            if (this->m_grid[neighborY][neighborX]) {
                count++;
            }
        }
    }

    return count;
}