#ifndef DUST_H
#define DUST_H

#include "element.h"
#include <stdlib.h>

class Dust: public Element {
public:
    const double FLAME = 1.0 / 64;
    const double PROCESS = 1.0 / 3;
    void process(SandSimulation *sim, int row, int col) override {
        if (randf() < FLAME && sim->touch_count(row, col, 5) > 0) {
            sim->set_cell(row, col, 5);
            return;
        }

        if (randf() > PROCESS || !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) != 0) {
            return;
        }
        int dir = (std::rand() % 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row + 1, col);
        }
    }

    double get_density() override {
        return 0.5;
    }
};

#endif // DUST_H