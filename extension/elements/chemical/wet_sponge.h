#pragma once




#include "../element.h"

class WetSponge: public Element {
public:
    const double BURN = 1.0 / 16;
    const double DRY = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < BURN && sim->is_on_fire(row, col) || sim->randf() < DRY && sim->touch_count(row, col, 0) > 0) {
            sim->set_cell(row, col, 99);
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    sim->grow(row + i, col + j, 0, 3);
                }
            }
        }

    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.6;
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

