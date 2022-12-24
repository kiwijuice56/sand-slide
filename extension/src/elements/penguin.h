#ifndef PENGUIN_H
#define PENGUIN_H

#include "element.h"

class Penguin: public Element {
public:
    const double GROWTH = 1.0 / 624;
    const double DEATH = 1.0 / 512;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 19) == 0 && sim->touch_count(row, col, 3) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 49) > 0 || sim->randf() < DEATH) {
            sim->set_cell(row, col, 19);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 19, 49);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 19, 49);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 19, 49);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 19, 49);
        } else if (sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 2.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // PENGUIN_H