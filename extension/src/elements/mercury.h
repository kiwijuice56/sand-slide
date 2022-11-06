#ifndef MERCURY_H
#define MERCURY_H

#include "element.h"
#include <stdlib.h>

class Mercury: public Element {
public:
    const double MELT = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        // Plasma melting
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->set_cell(row, col, 38);
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
        return 3.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // MERCURY_H