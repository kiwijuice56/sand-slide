#pragma once


#include "../element.h"
#include <stdlib.h>

class MoltenGold: public Element {
public:
    const double MELT = 1.0 / 80;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;
    const double COOL = 1.0 / 64;
    const double REG_COOL = 1.0 / 1500;

    void process(SandSimulation *sim, int row, int col) override {
        // Conductivity
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->set_cell(row, col, 38);
            return;
        }

        if (sim->randf() < COOL && (sim->is_cold(row, col) || sim->touch_count(row, col, 0) > 0) || sim->randf() < REG_COOL) {
            sim->set_cell(row, col, 51);
            return;
        }

        sim->liquid_process(row, col, 3);
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.80;
    }

    double get_acid_resistance() override {
        return 0.999;
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

