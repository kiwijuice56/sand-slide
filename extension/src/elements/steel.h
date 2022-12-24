#ifndef STEEL_H
#define STEEL_H

class SandSimulation;

#include "element.h"

class Steel: public Element {
public:
    const double PLASMA = 1.0 / 16;
    const double MELT = 1.0 / 2048;
    const double EXPLODE = 1.0 / 64;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 17, 38);
            sim->grow(row - 1, col, 17, 38);
            sim->grow(row, col - 1, 17, 38);
            sim->grow(row, col + 1, 17, 38);
            return;
        } else if (sim -> randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 44);
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