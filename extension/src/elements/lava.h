#ifndef LAVA_H
#define LAVA_H

#include "element.h"
#include <stdlib.h>

class Lava: public Element {
public:
    const double COOL = 1.0 / 256;
    const double FLAME = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Cooling
        if (sim->randf() < COOL && sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 2);
            return;
        }
        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
           sim->move_and_swap(row, col, row + 1, col);
        }
        if (sim->randf() < FLAME) {
            sim->grow(row - 1, col, 0, 5);
            sim->grow(row, col - 1, 0, 5);
            sim->grow(row, col + 1, 0, 5);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // LAVA_H