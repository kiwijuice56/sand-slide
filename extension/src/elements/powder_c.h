#ifndef POWDER_C_H
#define POWDER_C_H

#include "element.h"

class PowderC: public Element {
public:
    const double FLAME = 1 / 32.0;
    const double DISSOLVE = 1 / 256.0;
    const double POWDER = 1 / 1.125;

    // Duplicate of PowderA
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER){
            return;
        }

        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        } else if (sim -> randf() < DISSOLVE && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 43);
            return;
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.7;
    }

    double get_acid_resistance() override {
        return 0.6;
    }
};

#endif // POWDER_C_H