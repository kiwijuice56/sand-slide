#pragma once


#include "../element.h"

class Silver: public Element {
public:
    const double PLASMA = 1.0 / 8;
    const double MELT = 1.0 / 32;
    const double EXPLODE = 1.0 / 16;
    const double REACT = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 133, 38);
            sim->grow(row - 1, col, 133, 38);
            sim->grow(row, col - 1, 133, 38);
            sim->grow(row, col + 1, 133, 38);
            return;
        } else if (sim->randf() < MELT && (sim->touch_count(row, col, 20) + sim->touch_count(row, col, 24) > 0)) {
            sim->set_cell(row, col, 134);
        } else if (sim->randf() < EXPLODE && sim->touch_count(row, col, 23) + sim->touch_count(row, col, 32) > 0) {
            sim->set_cell(row, col, 9);
        }
        if (sim->randf() < REACT && sim->touch_count(row, col, 136) > 0) {
            sim->set_cell(row, col, 70);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.48;
    }

    double get_acid_resistance() override {
        return 0.98;
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

