#ifndef SAND_H
#define SAND_H

#include "element.h"

class Sand: public Element {
public:
    const double FLAME = 1 / 64.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 25);
            return;
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.2;
    }
};

#endif // SAND_H