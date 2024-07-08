#pragma once


#include "../element.h"

class Gold: public Element {
public:
    const double PLASMA = 1.0 / 8;
    const double MELT = 1.0 / 32;
    const double EXPLODE = 1.0 / 90;
    const double REACT = 1.0 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 51, 38);
            sim->grow(row - 1, col, 51, 38);
            sim->grow(row, col - 1, 51, 38);
            sim->grow(row, col + 1, 51, 38);
            return;
        } else if (sim -> randf() < MELT && (sim->touch_count(row, col, 20) + sim->touch_count(row, col, 24) > 0)) {
            sim->set_cell(row, col, 52);
        }

        if (sim->randf() < REACT && sim->touch_count(row, col, 136) > 0) {
            sim->set_cell(row, col, 70);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.64;
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

