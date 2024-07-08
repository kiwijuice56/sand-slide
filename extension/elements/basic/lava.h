#pragma once


#include "../element.h"
#include <stdlib.h>

class Lava: public Element {
public:
    const double COOL = 1.0 / 64;
    const double FLAME = 1.0 / 16;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;
    const double FIREWORK = 1.0 / 70;

    void process(SandSimulation *sim, int row, int col) override {
        // Cooling
        if (sim->randf() < COOL && (sim->is_cold(row, col) || sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0)) {
            sim->set_cell(row, col, 56);
            return;
        }

        sim->liquid_process(row, col, 2);

        if (sim->randf() < FLAME) {
            sim->grow(row - 1, col, 0, sim->randf() < FIREWORK ? 66 : 5);
            sim->grow(row, col - 1, 0, 5);
            sim->grow(row, col + 1, 0, 5);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.99;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

