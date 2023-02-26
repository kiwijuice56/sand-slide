#ifndef BURNING_OIL_H
#define BURNING_OIL_H

#include "../element.h"
#include <stdlib.h>

class BurningOil: public Element {
public:
    const double DECAY = 1.0 / 3048;
    const double BURN = 1.0 / 48;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    // Share the same properties as regular oil but spread flames to other oil while randomly burning off
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 6);
            return;
        }
        if (sim->randf() < BURN && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 0) {
            sim->grow(row - 1, col, -1, 5);
            return;
        }

        if (sim->is_cold(row, col)) {
            sim->set_cell(row, col, 30);
            return;
        }
        sim->liquid_process(row, col, 6); 
    }

    double get_density() override {
        return 0.8;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.6;
    }
};

#endif // BURNING_OIL_H