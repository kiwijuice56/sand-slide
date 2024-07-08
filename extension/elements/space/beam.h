#pragma once


#include "../element.h"

class Beam: public Element {
public:
    const double DECAY = 1.0 / 2;
    const double LIGHTNING = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != 94) {
            sim->set_cell(row, col, 0);
            return;
        }
        if (sim->randf() < LIGHTNING) {
            sim->grow(row, col - 1, -1, 114);
            sim->grow(row, col + 1, -1, 114);
        }
        sim->grow(row + 1, col, -1, 94);
        sim->grow(row + 2, col, -1, 94);
        sim->grow(row + 3, col, -1, 94);
    }

    double get_density() override {
        return 128.0;
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
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

