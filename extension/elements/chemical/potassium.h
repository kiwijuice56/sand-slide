#pragma once


#include "../element.h"

class Potassium: public Element {
public:
    const double FLAME = 1 / 90.0;
    const double WATER = 1 / 32.0;
    const double PLASMA = 1 / 18.0;
    const double POWDER = 1 / 1.025;
    const double OXIDIZE_A = 1.0 / 128;
    const double OXIDIZE_B = 1.0 / 400;
    const double FIREWORK = 1.0 / 24;
    const double REACT = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 45, 38);
            sim->grow(row - 1, col, 45, 38);
            sim->grow(row, col - 1, 45, 38);
            sim->grow(row, col + 1, 45, 38);
            return;
        }

        if (sim->randf() < WATER && sim->touch_count(row, col, 84) > 0) {
            sim->set_cell(row, col, 70);
            return;
        }

        if ((sim->randf() < OXIDIZE_A && sim->touch_count(row, col, 0) > 0) || (sim->randf() < OXIDIZE_B && sim->touch_count(row, col, 60) > 0)) {
            sim->set_cell(row, col, 60);
            return;
        }

        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 61);
        }

        // Make mini flashes of explosions in a square grid
        if (sim->randf() < WATER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            for (int y = -5; y <= 5; y++) {
                for (int x = -5; x <= 5; x++) {
                    if (y * y + x * x > 25) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 66 : 46);
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
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

