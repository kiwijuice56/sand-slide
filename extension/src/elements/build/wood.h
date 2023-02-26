#ifndef WOOD_H
#define WOOD_H

class SandSimulation;

#include "../element.h"

class Wood: public Element {
public:
    const double FLAME = 1.0 / 80;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
        }
    }

    double get_density() override {
        return 5.0;
    }

    double get_explode_resistance() override {
        return 0.3;
    }

    double get_acid_resistance() override {
        return 0.1;
    }
};

#endif // WOOD_H