#pragma once

#include <vector>
#include <iostream>

typedef std::vector<std::vector<bool>> BooleanGrid;

class Grid {
public:
    Grid(int size, int displaySize)
        : m_grid(BooleanGrid(size, std::vector<bool>(size, false)))
        , m_displayGrid(BooleanGrid(displaySize, std::vector<bool>(displaySize, false)))
        , m_displayX(int(size / 2 - displaySize / 2))
        , m_displayY(int(size / 2 - displaySize / 2))
        {
            if (size < displaySize)
                throw std::invalid_argument("Display size should be less than Size");
        };

    Grid(int size, int displaySize, int pctAlive) : Grid(size, displaySize)
        {
            this->randomizeCells(pctAlive);
        };

    void randomizeCells(int pctAlive);

    const BooleanGrid getDisplayGrid();

    void moveDisplayX(int value);
    void moveDisplayY(int value);

private:
    BooleanGrid m_grid;
    BooleanGrid m_displayGrid;
public:
    int         m_displayX;   // starting X point
    int         m_displayY;   // starting y point

    void updateDisplayGrid();
};