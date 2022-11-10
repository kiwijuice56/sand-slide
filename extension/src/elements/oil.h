#ifndef OIL_H
#define OIL_H

#include "element.h"
#include <stdlib.h>

class Oil: public Element {
public:
    const double FLAME = 1.0 / 32;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    void process(SandSimulation *sim, int row, int col) override {
        // Burning
        if (sim->randf() < FLAME && (sim->is_on_fire(row, col) || sim->touch_count(row, col, 6) > 0)) {
            sim->set_cell(row, col, 5);
            return;
        }

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 30;
        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) {
            sim->move_and_swap(row, col, row + 1, col);
        } else {
            sim->move_and_swap(row, col, row + (sim->randf() < DOWN_BLOCK ? 1 : 0), col + (sim->randf() < 0.5 ? 1 : -1));
        }
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

#endif // OIL_H