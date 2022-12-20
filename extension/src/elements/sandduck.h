#ifndef SAND_DUCK_H
#define SAND_DUCK_H

#include "element.h"

class SandDuck: public Element {
public:
    const double GROWTH = 0.008625;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 1) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 8) > 0) {
            sim->set_cell(row, col, 1);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + 1, col, 1, 8);
            sim->grow(row - 1, col, 1, 8);
            sim->grow(row, col - 1, 1, 8);
            sim->grow(row, col + 1, 1, 8);
        } else if (sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 2.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // SAND_DUCK_H