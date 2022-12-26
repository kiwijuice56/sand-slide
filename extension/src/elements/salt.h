#ifndef SALT_H
#define SALT_H

#include "element.h"

class Salt: public Element {
public:
    const double POWDER = 1 / 1.02;
    const double MIX = 1.0 / 4;
    
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < MIX && sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 71);
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 1.025;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.9;
    }
};

#endif // SALT_H