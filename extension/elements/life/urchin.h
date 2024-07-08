#pragma once


#include "../element.h"

// A salt and fresh water animal that grows similarly to dragons, but in water
class Urchin: public Element {
public:
    const double GROWTH = 0.000425;
    const double POISON = 1.0 / 16;
    const double AIR = 1.0 / 16;
    const double EAT = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < AIR && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 31) > 3 || sim->touch_count(row, col, 4) > 0) {
            sim->set_cell(row, col, sim->touch_count(row, col, 71) > sim->touch_count(row, col, 3) ? 71 : 3);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 3, 31);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 3, 31);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 3, 31);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 3, 31);

            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 71, 31);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 71, 31);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 71, 31);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 71, 31);
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
        } else if (sim->randf() < EAT) {
            int new_row = row + (sim->randf() < 0.5 ? 1 : -1);
            int new_col = col + (sim->randf() < 0.5 ? 1 : -1);
            sim->grow(new_row, new_col, 7, 31);
            sim->grow(new_row, new_col, 54, 31);
            sim->grow(new_row, new_col, 55, 31);
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.2;
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

