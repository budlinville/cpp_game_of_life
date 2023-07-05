#include "../include/Grid/grid.h"
#include "../include/Simulation/simulation.h"

int main() {
    int size = 10;

    Simulation sim(300, 30);
    sim.run();


    return 0;
}
