#pragma once


#include "../element.h"
#include <stdlib.h>

class LiquidPowder: public Element {
public:
    const double FLAME = 1.0 / 18;
    const double EXPLODE = 1.0 / 2;

    void process(SandSimulation *sim, int row, int col) override {
        // Burning
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (sim->in_bounds(row + y, col + x) && x * x + y * y < 28.0) {
                        sim->set_cell(row + y, col + x, sim->randf() < EXPLODE ? 66 : 9);
                    }
                }
            }
            return;
        }

        sim->liquid_process(row, col, 4);
    }

    double get_density() override {
        return 0.9;
    }

    double get_explode_resistance() override {
        return 0.1;
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

