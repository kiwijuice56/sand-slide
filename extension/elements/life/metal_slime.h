#pragma once


#include "../element.h"
#include <stdlib.h>

class MetalSlime: public Element {
public:
    const double CLIMB = 1.0 / 128;
    const double MELT = 1.0 / 128;
    const double SLIME = 4;
    const double PLASMA = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 132, 38);
            sim->grow(row - 1, col, 132, 38);
            sim->grow(row, col - 1, 132, 38);
            sim->grow(row, col + 1, 132, 38);
        }

        if (sim->randf() <= MELT) {
            sim->grow(row + 1, col, -1, 132);
        }

        if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) == 0 && sim->cardinal_touch_count(row, col + 1, 0) >= 1) {
            int x = sim->touch_count(row, col + 1, 132), y = sim->touch_count(row, col + 1, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row, col + 1, 0, 132);
        }
        if (sim->in_bounds(row, col - 1) && sim->get_cell(row, col - 1) == 0 && sim->cardinal_touch_count(row, col - 1, 0) >= 1) {
            int x = sim->touch_count(row, col - 1, 132), y = sim->touch_count(row, col - 1, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row, col - 1, 0, 132);
        }
        if (sim->in_bounds(row + 1, col) && sim->get_cell(row + 1, col) == 0 && sim->cardinal_touch_count(row + 1, col, 0) >= 1) {
            int x = sim->touch_count(row + 1, col, 132), y = sim->touch_count(row + 1, col, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row + 1, col, 0, 132);
        }
        if (sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 0 && sim->cardinal_touch_count(row - 1, col, 0) >= 1) {
            int x = sim->touch_count(row - 1, col, 132), y = sim->touch_count(row - 1, col, 0);
            if ((sim->randf() >= CLIMB && x + y == 8) || sim->randf() >= 1.0 / (SLIME * (x + y))) {
                return;
            }
            sim->grow(row - 1, col, 0, 132);
        }

    }

    double get_density() override {
        return 100.0;
    }

    double get_explode_resistance() override {
        return 1.0;
    }

    double get_acid_resistance() override {
        return 1.0;
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

