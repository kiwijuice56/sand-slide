#ifndef GOLD_H
#define GOLD_H

class SandSimulation;

#include "element.h"

class Gold: public Element {
public:
    const double PLASMA = 1.0 / 8;
    const double MELT = 1.0 / 290;
    const double EXPLODE = 1.0 / 90;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 51, 38);
            sim->grow(row - 1, col, 51, 38);
            sim->grow(row, col - 1, 51, 38);
            sim->grow(row, col + 1, 51, 38);
            return;
        } else if (sim -> randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 52);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.64;
    }

    double get_acid_resistance() override {
        return 0.999;
    }
};

#endif // GOLD_H