#pragma once


#include "../element.h"

class JavelinRain: public Element {
public:
    const double DECAY = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            if (sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 128) return;
            if (sim->in_bounds(row - 1, col - 1) && sim->get_cell(row - 1, col - 1) == 128) return;
            if (sim->in_bounds(row - 1, col + 1) && sim->get_cell(row - 1, col + 1) == 128) return;
            sim->set_cell(row, col, 6);
            return;
        }
        sim->set_cell(row, col, 0);
        sim->grow(row + 4, col - 1, -1, 128);
        sim->grow(row + 4, col + 1, -1, 128);
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
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

