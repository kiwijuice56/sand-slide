#pragma once


#include "../element.h"

// A fresh water frog that slowly builds populations over time
class Polliwog: public Element {
public:
    const double GROWTH = 1.0 / 550;
    const double DEATH = 1.0 / 512;
    const double BAD_ENVIRONMENT = 1.0 / 16;
    const double AIR_DEATH = 1.0 / 16;
    const double EAT = 1.0 / 128;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < AIR_DEATH && sim->touch_count(row, col, 3) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 4) > 1 || sim->touch_count(row, col, 31) > 0 || sim->randf() < DEATH) {
            sim->set_cell(row, col, 3);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 3, 4);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 3, 4);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 3, 4);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 3, 4);
        } else if (sim->randf() < BAD_ENVIRONMENT && (sim->is_cold(row, col) || sim->is_poisoned(row, col) || sim->touch_count(row, col, 71))) {
            sim->set_cell(row, col, 16);
        } else if (sim->randf() < EAT) {
            int new_row = row + (sim->randf() < 0.5 ? 1 : -1);
            int new_col = col + (sim->randf() < 0.5 ? 1 : -1);
            sim->grow(new_row, new_col, 7, 4); // Eat algae by turning it into water
            sim->grow(new_row, new_col, 54, 4);
            sim->grow(new_row, new_col, 55, 4);
            sim->grow(new_row, new_col, 23, 16); // Eat fairies by turning them into dust
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.4;
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

