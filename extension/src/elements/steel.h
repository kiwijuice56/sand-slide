#ifndef STEEL_H
#define STEEL_H

class SandSimulation;

#include "element.h"

class Steel: public Element {
public:
    const double MELT = 1.0 / 16;
    const double EXPLODE = 1.0 / 8;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < MELT && sim->touch_count(row, col, 38) + sim->touch_count(row, col, 39) > 0) {
            sim->set_cell(row, col, sim->randf() < EXPLODE ? 9 : 38);
        }
    }

    double get_density() override {
        return 48.0;
    }

    double get_explode_resistance() override {
        return 0.95;
    }

    double get_acid_resistance() override {
        return 0.95;
    }
};

#endif // STEEL_H