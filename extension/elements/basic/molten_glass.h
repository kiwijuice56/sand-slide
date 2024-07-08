#pragma once




#include "../element.h"

class MoltenGlass: public Element {
public:
    const double COOL = 1.0 / 32;
    const double SPREAD = 1.0 / 24;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < COOL || sim->is_cold(row, col)) {
            sim->set_cell(row, col, 25);
            return;
        }

        if (sim->randf() < SPREAD) {
            sim->grow(row + 1, col, 1, 53);
            sim->grow(row - 1, col, 1, 53);
            sim->grow(row, col - 1, 1, 53);
            sim->grow(row, col + 1, 1, 53);
            sim->grow(row + 1, col, 98, 53);
            sim->grow(row - 1, col, 98, 53);
            sim->grow(row, col - 1, 98, 53);
            sim->grow(row, col + 1, 98, 53);
        }
    }

    double get_density() override {
        return 3.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.95;
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

