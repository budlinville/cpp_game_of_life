#include "../include/Grid/grid.h"
#include "../include/Simulation/simulation.h"

int main() {
    Simulation sim(1000, 30);
    sim.run();

    return 0;
}
