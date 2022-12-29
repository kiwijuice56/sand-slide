#ifndef IODINE_H
#define IODINE_H

#include "element.h"

class Iodine: public Element {
public:
    const double POWDER = 1 / 1.02;
    const double DECAY = 1.0 / 800;
    const double MELT = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < DECAY && sim->touch_count(row, col, 0) > 0) {
            sim->set_cell(row, col, 83);
            return;
        }

        if (sim->randf() < MELT && sim->touch_count(row, col, 24) + sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 84);
            return;
        }

        bool bot_left = sim->is_swappable(row, col, row + 1, col - 1);
        bool bot = sim->is_swappable(row, col, row + 1, col);
        bool bot_right = sim->is_swappable(row, col, row + 1, col + 1);
        if (bot) {
            sim->move_and_swap(row, col, row + 1, col);
        } else if (bot_left && bot_right) {
            sim->move_and_swap(row, col, row + 1, col + (sim->randf() < 0.5 ? 1 : -1));
        } else if (bot_left) {
            sim->move_and_swap(row, col, row + 1, col - 1);
        } else if (bot_right) {
            sim->move_and_swap(row, col, row + 1, col + 1);
        }
    }

    double get_density() override {
        return 8.1;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.8;
    }
};

#endif // IODINE_H