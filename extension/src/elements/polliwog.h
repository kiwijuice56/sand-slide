#ifndef POLLIWOG_H
#define POLLIWOG_H

#include "element.h"

class Polliwog: public Element {
public:
    const double GROWTH = 0.015625;

    void process(SandSimulation *sim, int row, int col) override {
        int water_cells = sim->touch_count(row, col, 3);
        if (water_cells == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 4) > 0) {
            sim->set_cell(row, col, 3);
        } else if (randf() < GROWTH) {
            sim->grow(row + 1, col, 3, 4);
            sim->grow(row - 1, col, 3, 4);
            sim->grow(row, col - 1, 3, 4);
            sim->grow(row, col + 1, 3, 4);
        } else if (sim->touch_count(row, col, 10)) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 1.25;
    }
};

#endif // POLLIWOG_H