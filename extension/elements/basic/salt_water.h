#pragma once


#include "../element.h"
#include <stdlib.h>

class SaltWater: public Element {
public:
    const double ABSORB = 1.0 / 4098;
    const double EVAPORATION = 1.0 / 64;
    const double MELT = 1.0 / 16;
    const double MIX = 1.0 / 4;
    const double FREEZE = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        // Conductivity
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 71, 38);
            sim->grow(row - 1, col, 71, 38);
            sim->grow(row, col - 1, 71, 38);
            sim->grow(row, col + 1, 71, 38);
            return;
        }

        if (sim->randf() < FREEZE && sim->is_cold(row, col)) {
            sim->set_cell(row, col, sim->randf() < 0.5 ? 19 : 85);
        }

        // Mix with water to turn into acidic water
        if (sim->randf() < MIX && sim->touch_count(row, col, 21) > 0) {
            sim->set_cell(row, col, 59);
            return;
        }

        if (sim->randf() < MIX && sim->touch_count(row, col, 70) > 0) {
            sim->set_cell(row, col, 71);
            return;
        }

        // Evaporation when heated
        if (sim->randf() < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, sim->randf() < 0.5 ? 58 : 70);
            return;
        }

        sim->liquid_process(row, col, 2);
    }

    double get_density() override {
        return 1.05;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.9;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

