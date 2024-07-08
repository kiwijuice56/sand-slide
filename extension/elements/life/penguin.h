#pragma once


#include "../element.h"

class Penguin: public Element {
public:
    const double GROWTH = 1.0 / 624;
    const double DEATH = 1.0 / 512;
    const double POISON = 1.0 / 16;
    const double AIR = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < AIR && (sim->touch_count(row, col, 19) + sim->touch_count(row, col, 85) == 0) && sim->touch_count(row, col, 3) == 0) {
            sim->set_cell(row, col, 0);
        } else if (sim->touch_count(row, col, 49) > 1 || sim->randf() < DEATH) {
            sim->set_cell(row, col, 19);
        } else if (sim->randf() < GROWTH) {
            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 19, 49);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 19, 49);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 19, 49);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 19, 49);

            sim->grow(row + (sim->randf() < 0.5 ? 1 : 2), col, 85, 49);
            sim->grow(row - (sim->randf() < 0.5 ? 1 : 2), col, 85, 49);
            sim->grow(row, col - (sim->randf() < 0.5 ? 1 : 2), 85, 49);
            sim->grow(row, col + (sim->randf() < 0.5 ? 1 : 2), 85, 49);
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 2.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.3;
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

