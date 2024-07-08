#pragma once


#include "../element.h"

class Iron: public Element {
public:
    const double PLASMA = 1.0 / 16;
    const double MELT = 1.0 / 2048;
    const double EXPLODE = 1.0 / 64;
    const double RUST_A = 1.0 / 2048;
    const double RUST_B = 1.0 / 3048;
    const double RUST_C = 1.0 / 800;
    const double DISSOLVE = 1.0 / 512;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 17, 38);
            sim->grow(row - 1, col, 17, 38);
            sim->grow(row, col - 1, 17, 38);
            sim->grow(row, col + 1, 17, 38);
        } else if (sim->randf() < DISSOLVE && sim->touch_count(row, col, 118) > 0) {
            sim->set_cell(row, col, 118);
        } else if (sim -> randf() < MELT && (sim->touch_count(row, col, 20) + sim->touch_count(row, col, 24) > 0)) {
            sim->set_cell(row, col, 20);
        } else if ((sim->randf() < RUST_A && sim->touch_count(row, col, 3) > 0) || (sim->randf() < RUST_B && sim->touch_count(row, col, 62) > 0)
        || (sim->randf() < RUST_C && sim->touch_count(row, col, 71) > 0) )  {
            sim->set_cell(row, col, 62);
        }
    }

    double get_density() override {
        return 48.0;
    }

    double get_explode_resistance() override {
        return 0.95;
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

