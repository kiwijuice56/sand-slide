#ifndef DRAGON_H
#define DRAGON_H

#include "element.h"

class Dragon: public Element {
public:
    const double GROWTH = 0.010625;
    const double DISSOLVE = 1.0 / 128;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 32) > 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 23) > 0 || randf() < DISSOLVE && sim->touch_count(row, col, 30) > 0) {
            sim->set_cell(row, col, 16);
        } else if (randf() < GROWTH * (sim->is_on_fire(row, col) ? 12.0 : 1.0)) {
            int dir = (std::rand() % 2) - 1;
            if (dir == 0) {
                sim->grow(row - 1, col - 1, 0, 32);
                sim->grow(row + 1, col + 1, 0, 32);
            } else {
                sim->grow(row, col - 1, 0, 32);
                sim->grow(row, col + 1, 0, 32);
            }
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.99;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // DRAGON_H