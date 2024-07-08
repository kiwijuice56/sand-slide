#pragma once


#include "../element.h"

class NeutronBeam: public Element {
public:
    const double DECAY = 1.0 / 2;
    const double EXPLODE = 1.0 / 164;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != 36) {
            sim->set_cell(row, col, 22);
            return;
        }

        if (sim->randf() < EXPLODE && sim->in_bounds(row + 1, col) && sim->get_cell(row + 1, col) != 0 && sim->get_cell(row + 1, col) != 29 && sim->get_cell(row + 1, col) != 15) {
            sim->grow(row + 1, col + 1, -1, 34);
            sim->grow(row + 1, col, -1, 34);
            sim->grow(row + 1, col - 1, -1, 34);
        } else {
            sim->grow(row + 1, col, -1, 36);
            sim->grow(row + 2, col, -1, 36);
        }
    }

    double get_density() override {
        return 256.0;
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

