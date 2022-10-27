#ifndef ALGAE_H
#define ALGAE_H

#include "element.h"

class Algae: public Element {
public:
    const double GROWTH = 1.0 / 2048;
    const double DEATH = 1.0 / 6000;
    const double FLAME = 1.0 / 48;

    void process(SandSimulation *sim, int row, int col) override {  
        // Catch on fire
        if (sim->touch_count(row, col, 5) > 0 && randf() < FLAME) {
            sim->set_cell(row, col, 5);
            return;
        }

        // Grow into water
        int water_cells = sim->touch_count(row, col, 3);
        if (water_cells > 0 && randf() < GROWTH) {
            sim->grow(row + (std::rand() % 2) - 1, col + std::rand() % 2 - 1, 3, 7);
        }
        else if (randf() < DEATH) {
            sim->set_cell(row, col, 3);
        }
    }

    double get_density() override {
        return 1.25;
    }
};

#endif // ALGAE_H