#pragma once


#include "../element.h"

class FireworkTrailD: public Element {
public:
    const double POWDER = 1 / 1.5;
    const double DECAY = 1.0 / 24;
    const double FLAME = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, sim->randf() < FLAME ? 0 : 0);
            return;
        }

        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 4.0;
    }

    double get_explode_resistance() override {
        return 0.4;
    }

    double get_acid_resistance() override {
        return 0.2;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

