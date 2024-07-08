#pragma once


#include "../element.h"
#include <stdlib.h>

class Slime: public Element {
public:
    const double FLAME = 1.0 / 8;
    const double GROW = 1.0 / 2;
    const double CLIMB = 1.0 / 128;
    const double MELT = 1.0 / 128;
    const double SLIME = 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() >= GROW) {
            return;
        }

        if (sim->randf() <= MELT) {
            sim->grow(row + 1, col, -1, 86);
        }

        if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) == 0 && sim->cardinal_touch_count(row, col + 1, 0) >= 1) {
            int x = sim->touch_count(row, col + 1, 86), y = sim->touch_count(row, col + 1, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row, col + 1, 0, 86);
        }
        if (sim->in_bounds(row, col - 1) && sim->get_cell(row, col - 1) == 0 && sim->cardinal_touch_count(row, col - 1, 0) >= 1) {
            int x = sim->touch_count(row, col - 1, 86), y = sim->touch_count(row, col - 1, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row, col - 1, 0, 86);
        }
        if (sim->in_bounds(row + 1, col) && sim->get_cell(row + 1, col) == 0 && sim->cardinal_touch_count(row + 1, col, 0) >= 1) {
            int x = sim->touch_count(row + 1, col, 86), y = sim->touch_count(row + 1, col, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row + 1, col, 0, 86);
        }
        if (sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 0 && sim->cardinal_touch_count(row - 1, col, 0) >= 1) {
            int x = sim->touch_count(row - 1, col, 86), y = sim->touch_count(row - 1, col, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row - 1, col, 0, 86);
        }

    }

    double get_density() override {
        return 0.5;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.99;
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

