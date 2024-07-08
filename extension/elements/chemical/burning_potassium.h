#pragma once


#include "../element.h"

class BurningPotassium: public Element {
public:
    const double DECAY = 1.0 / 512;
    const double PLASMA = 1 / 18.0;
    const double BURN = 1.0 / 48;
    const double POWDER = 1 / 1.025;
    const double WATER = 1 / 32.0;
    const double REACT = 1.0 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 61, 38);
            sim->grow(row - 1, col, 61, 38);
            sim->grow(row, col - 1, 61, 38);
            sim->grow(row, col + 1, 61, 38);
            return;
        }

        if (sim->randf() < WATER && sim->touch_count(row, col, 84) > 0) {
            sim->set_cell(row, col, 70);
            return;
        }

        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < DECAY && sim->touch_count(row, col, 0) > 0) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() < BURN && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 0) {
            sim->grow(row - 1, col, 0, 5);
            return;
        }

        if (sim->randf() < WATER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (y * y + x * x > 36) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, 46);
                    }
                }
            }
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

        if (sim->randf() < REACT && sim->touch_count(row, col, 136) > 0) {
            sim->set_cell(row, col, 70);
        }
    }

    double get_density() override {
        return 6.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.89;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

