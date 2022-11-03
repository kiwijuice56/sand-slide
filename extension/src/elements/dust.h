#ifndef DUST_H
#define DUST_H

#include "element.h"
#include <stdlib.h>

class Dust: public Element {
public:
    const double FLAME = 1.0 / 64;
    const double PROCESS = 1.0 / 3;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        if (sim->randf() > PROCESS || !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) != 0) {
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
        return 0.5;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // DUST_H