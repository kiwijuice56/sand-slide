#pragma once


#include "../element.h"

class FreezeRay: public Element {
public:
    const double DECAY = 1.0 / 1.5;
    const double DESTROY = 1.0 / 8;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != 153) {
            sim->set_cell(row, col, 89);
            return;
        }
        if (sim->randf() < DESTROY) {
            sim->grow(row + 1, col, -1, 153);
            sim->grow(row + 2, col, -1, 153);
        } else {
            sim->grow(row + 1, col, 0, 153);
            sim->grow(row + 2, col, 0, 153);
        }
    }

    double get_density() override {
        return 4.0;
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
        return -1;
    }

    int get_toxicity() override {
        return 0;
    }
};

