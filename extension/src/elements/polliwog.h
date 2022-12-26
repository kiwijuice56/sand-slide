#ifndef POLLIWOG_H
#define POLLIWOG_H

#include "element.h"

class Polliwog: public Element {
public:
    const double GROWTH = 1.0 / 550;
    const double DEATH = 1.0 / 512;
    const double POISON = 1.0 / 8;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 3) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 4) > 1 || sim->touch_count(row, col, 31) > 0 || sim->randf() < DEATH) {
            sim->set_cell(row, col, 3);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 3, 4);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 3, 4);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 3, 4);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 3, 4);
        } else if (sim->randf() < POISON && (sim->is_poisoned(row, col) || sim->touch_count(row, col, 71))) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // POLLIWOG_H