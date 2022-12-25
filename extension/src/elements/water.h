#ifndef WATER_H
#define WATER_H

#include "element.h"
#include <stdlib.h>

class Water: public Element {
public:
    const double ABSORB = 1.0 / 4098;
    const double EVAPORATION = 1.0 / 128;
    const double MELT = 1.0 / 64;
    const double DOWN = 1.0 / 1.2;
    const double DOWN_BLOCK = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Plasma melting
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 3, 38);
            sim->grow(row - 1, col, 3, 38);
            sim->grow(row, col - 1, 3, 38);
            sim->grow(row, col + 1, 3, 38);
            return;
        }

        // Evaporation
        if (sim->randf() < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // Absorption
        if (sim->randf() < ABSORB && sim->touch_count(row, col, 14) > 0) {
            sim->set_cell(row, col, 0);
            return;
        }

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 3;
        
        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) 
            sim->move_and_swap(row, col, row + 1, col);
        else 
            sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
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