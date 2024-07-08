#pragma once




#include "../element.h"

class InfoDust: public Element {
public:
    const double DECAY = 1 / 16.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        }
    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.01;
    }

    double get_acid_resistance() override {
        return 0.01;
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

