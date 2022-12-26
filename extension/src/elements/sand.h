#ifndef SAND_H
#define SAND_H

#include "element.h"

class Sand: public Element {
public:
    const double FLAME = 1 / 64.0;
    const double POWDER = 1 / 1.05;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 53);
            return;
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.2;
    }
};

#endif // SAND_H