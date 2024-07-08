#pragma once


#include "../element.h"
#include <stdlib.h>

class Oil: public Element {
public:
    const double FLAME = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        // Burning
        if (sim->randf() < FLAME && (sim->is_on_fire(row, col) || sim->touch_count(row, col, 6) > 0)) {
            sim->set_cell(row, col, 50);
            return;
        }

        sim->liquid_process(row, col, 3);
    }

    double get_density() override {
        return 0.8;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.6;
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

