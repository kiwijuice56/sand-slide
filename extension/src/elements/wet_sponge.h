#ifndef WET_SPONGE_H
#define WET_SPONGE_H

class SandSimulation;

#include "element.h"

class WetSponge: public Element {
public:
    const double DRY = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DRY && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 99);
            sim->grow(row + 1, col, 0, 3);
            sim->grow(row - 1, col, 0, 3);
            sim->grow(row, col + 1, 0, 3);
            sim->grow(row, col - 1, 0, 3);

            sim->grow(row + 1, col + 1, 0, 3);
            sim->grow(row - 1, col + 1, 0, 3);
            sim->grow(row - 1, col - 1, 0, 3);
            sim->grow(row + 1, col - 1, 0, 3);
        }
        
    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // WET_SPONGE_H