#ifndef POWDER_H
#define POWDER_H

#include "element.h"

class Powder: public Element {
public:
    const double FLAME = 1 / 64.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 16);
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

#endif // POWDER_H