#include "../include/Grid/grid.h"
#include "../include/Simulation/simulation.h"

int main() {
    int size = 10;

    Grid grid = Grid(5000, 100, 30);
    Simulation sim = Simulation(grid);
    sim.run();


    return 0;
}
