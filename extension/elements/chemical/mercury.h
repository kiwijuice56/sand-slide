#pragma once


#include "../element.h"
#include <stdlib.h>

class Mercury: public Element {
public:
    const double MELT = 1.0 / 4;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    void process(SandSimulation *sim, int row, int col) override {
        // Conductivity
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->set_cell(row, col, 38);
            return;
        }

        sim->liquid_process(row, col, 4);
    }

    double get_density() override {
        return 16.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.99;
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

