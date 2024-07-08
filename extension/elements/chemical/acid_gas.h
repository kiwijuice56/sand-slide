#pragma once


#include "../element.h"

class AcidGas: public Element {
public:
    const double DECAY = 1.0 / 160;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY)  {
            sim->set_cell(row, col, 0);
        }

        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

