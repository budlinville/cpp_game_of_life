#pragma once

#include <vector>
#include <iostream>

typedef std::vector<std::vector<bool>> BooleanGrid;

class Grid {
public:
    Grid()
        : m_grid(BooleanGrid(50, std::vector<bool>(50, false)))
        , m_displayGrid(BooleanGrid(10, std::vector<bool>(10, false)))
        , m_displayX(20)
        , m_displayY(20)
    {}

    Grid(int size, int displayWidth, int displayHeight)
        : m_grid(BooleanGrid(size, std::vector<bool>(size, false)))
        , m_displayGrid(BooleanGrid(displayHeight, std::vector<bool>(displayWidth, false)))
        , m_displayX(int(size / 2 - displayWidth / 2))
        , m_displayY(int(size / 2 - displayHeight / 2))
        {
            if (size < displayWidth || size < displayHeight)
                throw std::invalid_argument("Display Width/Height should be less than or equal to Size");
        };

    Grid(int size, int displayWidth, int displayHeight, int pctAlive) : Grid(size, displayWidth, displayHeight)
        {
            this->randomizeCells(pctAlive);
        };
    
    Grid(const Grid& other)
        : m_grid(other.m_grid)
        , m_displayGrid(other.m_displayGrid)
        , m_displayX(other.m_displayX)
        , m_displayY(other.m_displayY)
        {}

    // TODO: member variables should really be private with getters... Made public as convenience for copy constructor and assignment operator
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            m_grid = other.m_grid;
            m_displayGrid = other.m_displayGrid;
            m_displayX = other.m_displayX;
            m_displayY = other.m_displayY;
        }
        return *this;
    }

    void randomizeCells(int pctAlive);

    const BooleanGrid getDisplayGrid();

    void moveDisplayX(int value);
    void moveDisplayY(int value);
    void incrementGrid();

private:
    int getSurroundingAliveCells(int x, int y);

public:
    BooleanGrid m_grid;
    BooleanGrid m_displayGrid;
    int         m_displayX;   // starting X point
    int         m_displayY;   // starting y point

    void updateDisplayGrid();
};