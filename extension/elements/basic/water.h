#pragma once


#include "../element.h"

class Water: public Element {
public:
    const double ABSORB = 1.0 / 2048;
    const double MELT = 1.0 / 128;
    const double EVAPORATION = 1.0 / 64;
    const double MIX = 1.0 / 32;
    const double FREEZE = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        double random = sim->randf();

        // Absorption into plants
        if (random < ABSORB && (sim->cardinal_touch_count(row, col, 14) +  sim->cardinal_touch_count(row, col, 169)) > 0) {
            sim->set_cell(row, col, 0);
            return;
        }

        // Conductivity
        if (random < MELT && (sim->cardinal_touch_count(row, col, 38) > 0 || sim->cardinal_touch_count(row, col, 40) > 0 || sim->cardinal_touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 3, 38);
            sim->grow(row - 1, col, 3, 38);
            sim->grow(row, col - 1, 3, 38);
            sim->grow(row, col + 1, 3, 38);
            return;
        }

        // Evaporation when heated
        if (random < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // Mix with acid to turn into acidic water
        if (random < MIX && sim->cardinal_touch_count(row, col, 21) > 0) {
            sim->set_cell(row, col, 59);
            return;
        }

        if (random < MIX && sim->cardinal_touch_count(row, col, 70) > 0) {
            sim->set_cell(row, col, 71);
            return;
        }

        if (random < FREEZE && sim->is_cold(row, col)) {
            sim->set_cell(row, col, sim->randf() < 0.5 ? 19 : 85);
            return;
        }

        sim->liquid_process(row, col, 2);
    }

    double get_density() override {
        return 1.0;
    }

    double get_explode_resistance() override {
        return 0.2;
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

