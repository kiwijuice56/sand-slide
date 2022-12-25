#ifndef COOL_LAVA_H
#define COOL_LAVA_H

#include "element.h"
#include <stdlib.h>

class CoolLava: public Element {
public:
    const double MOVE = 1.0 / 2;
    const double COOL = 1.0 / 48;
    const double SPREAD = 1.0 / 42;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    // Slightly slower than lava, spreading until it cools into obsidian
    void process(SandSimulation *sim, int row, int col) override {
        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 20;
        if (sim->randf() < MOVE) {
            if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) {
                sim->move_and_swap(row, col, row + 1, col);
            } else {
                sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
            }
        }
        if (sim->randf() < COOL) {
            sim->set_cell(row, col, 57);
        } if (sim->randf() < SPREAD) {
            sim->grow(row + 1, col, 20, 56);
            sim->grow(row - 1, col, 20, 56);
            sim->grow(row, col - 1, 20, 56);
            sim->grow(row, col + 1, 20, 56);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // COOL_LAVA_H