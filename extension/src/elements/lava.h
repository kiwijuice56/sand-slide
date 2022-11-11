#ifndef LAVA_H
#define LAVA_H

#include "element.h"
#include <stdlib.h>

class Lava: public Element {
public:
    const double COOL = 1.0 / 256;
    const double FLAME = 1.0 / 16;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    void process(SandSimulation *sim, int row, int col) override {
        // Cooling
        if (sim->randf() < COOL && sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 2);
            return;
        }

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 20;
        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) {
            sim->move_and_swap(row, col, row + 1, col);
        } else {
            sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
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