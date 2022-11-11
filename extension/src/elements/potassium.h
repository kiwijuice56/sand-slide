#ifndef POTASSIUM_H
#define POTASSIUM_H

#include "element.h"

class Potassium: public Element {
public:
    const double FLAME = 1 / 64.0;
    const double WATER = 1 / 32.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 46);
        }
        else if (sim->randf() < WATER && sim->touch_count(row, col, 3)) {
            for (int y = -3; y <= 3; y++) {
                for (int x = -3; x <= 3; x++) {
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, 46);
                    }
                }
            }
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 4.0;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.89;
    }
};

#endif // POTASSIUM_H