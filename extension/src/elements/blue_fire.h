#ifndef BLUE_FIRE_H
#define BLUE_FIRE_H

#include "element.h"

class BlueFire: public Element {
public:
    const double DECAY = 1.0 / 460; 
    const double UP = 1.0 / 1.5;
    const double UP_BLOCK = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Extinguish 
        if (sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 6);
        }

        bool blocked = !sim->in_bounds(row - 1, col) || sim->get_cell(row - 1, col) == 24;
        if (sim->randf() < (blocked ? UP_BLOCK : UP)) {
            sim->move_and_swap(row, col, row - 1, col);
        } else {
            sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
        }
    }

    double get_density() override {
        return 0.45;
    }

    double get_explode_resistance() override {
        return 0.25;
    }

    double get_acid_resistance() override {
        return 0.25;
    }
};

#endif // BLUE_FIRE_H