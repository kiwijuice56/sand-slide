#pragma once


#include "../element.h"

class Glitch: public Element {
public:
    const double DECAY = 1.0 / 256;
    const double VOID = 1.0 / 1.25;
    const double GROW = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            if (sim->randf() < VOID) {
                sim->set_cell(row, col, 0);
            } else {
                sim->set_cell(row, col, int(sim->randf() * 116));
            }
            return;
        }
        if (sim->randf() < GROW) {
            sim->grow(row + 1, col, -1, 117);
            sim->grow(row, col + 1, -1, 117);
            sim->grow(row - 1, col, -1, 117);
            sim->grow(row, col - 1, -1, 117);
        }

    }

    double get_density() override {
        return 999.0;
    }

    double get_explode_resistance() override {
        return 1.0;
    }

    double get_acid_resistance() override {
        return 1.0;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 1.0;
    }

    int get_toxicity() override {
        return 0;
    }
};

