#ifndef URCHIN_H
#define URCHIN_H

#include "element.h"

class Urchin: public Element {
public:
    const double GROWTH = 0.000425;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 3) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 31) > 3 || sim->touch_count(row, col, 4) > 0) {
            sim->set_cell(row, col, 3);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 3, 31);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 3, 31);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 3, 31);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 3, 31);
        } else if (sim->is_poisoned(row, col)) {
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

#endif // URCHIN_H