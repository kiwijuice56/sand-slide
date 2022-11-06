#ifndef LIQUID_POWDER_H
#define LIQUID_POWDER_H

#include "element.h"
#include <stdlib.h>

class LiquidPowder: public Element {
public:
    const double FLAME = 1.0 / 18;

    void process(SandSimulation *sim, int row, int col) override {
        // Burning
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 9);
            return;
        }

        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row + 1, col);
        }
    }

    double get_density() override {
        return 0.9;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.9;
    }
};

#endif // LIQUID_POWDER_H