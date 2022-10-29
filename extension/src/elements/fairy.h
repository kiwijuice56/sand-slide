#ifndef FAIRY_H
#define FAIRY_H

#include "element.h"

class Fairy: public Element {
public:
    const double GROWTH = 0.015625;
    const double DISSOLVE = 1.0 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 23) > 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 32) > 0 || randf() < DISSOLVE && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 16);
        } else if (randf() < GROWTH * (sim->is_on_fire(row, col) ? 6.0 : 1.0)) {
            int dir = (std::rand() % 2) - 1;
            if (dir == 0) {
                sim->grow(row - 1, col, 0, 23);
                sim->grow(row + 1, col, 0, 23);
            } else {
                sim->grow(row, col - 1, 0, 23);
                sim->grow(row, col + 1, 0, 23);
            }
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.55;
    }

    double get_acid_resistance() override {
        return 0.85;
    }
};

#endif // FAIRY_H