#ifndef WATER_H
#define WATER_H

#include "element.h"
#include <stdlib.h>

class Water: public Element {
public:
    const double ABSORB = 1.0 / 4098;
    const double EVAPORATION = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        // Evaporation
        if (randf() < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        }

        // Absorption
        if (randf() < ABSORB && sim->touch_count(row, col, 14) > 0) {
            sim->set_cell(row, col, 0);
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
        return 1.0;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.9;
    }
};

#endif // WATER_H