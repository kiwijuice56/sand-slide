#pragma once


#include "../element.h"

class Blood: public Element {
public:
    const double ABSORB = 1.0 / 64;
    const double EVAPORATION = 1.0 / 64;
    const double MELT = 1.0 / 64;
    const double MIX = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        // Conductivity
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 3, 38);
            sim->grow(row - 1, col, 3, 38);
            sim->grow(row, col - 1, 3, 38);
            sim->grow(row, col + 1, 3, 38);
            return;
        }

        // Evaporation when heated
        if (sim->randf() < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // Absorption into plants
        if (sim->randf() < ABSORB && sim->touch_count(row, col, 14) > 0) {
            sim->set_cell(row, col, 0);
            return;
        }

        sim->liquid_process(row, col, 1);
    }

    double get_density() override {
        return 1.1;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.3;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

