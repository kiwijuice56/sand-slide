#ifndef MERCURY_H
#define MERCURY_H

#include "element.h"
#include <stdlib.h>

class Mercury: public Element {
public:
    const double MELT = 1.0 / 64;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    void process(SandSimulation *sim, int row, int col) override {
        // Plasma melting
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->set_cell(row, col, 38);
            return;
        }

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 44;
        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) {
            sim->move_and_swap(row, col, row + 1, col);
        } else {
            sim->move_and_swap(row, col, row + (sim->randf() < DOWN_BLOCK ? 1 : 0), col + (sim->randf() < 0.5 ? 1 : -1));
        }
    }

    double get_density() override {
        return 16.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // MERCURY_H