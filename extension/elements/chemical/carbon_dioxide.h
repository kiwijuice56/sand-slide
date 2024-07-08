#pragma once


#include "../element.h"
#include <stdlib.h>

class CarbonDioxide: public Element {
public:
    const double DECAY = 1.0 / 1024;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim ->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        }
        sim->liquid_process(row, col, 2);
    }

    double get_density() override {
        return 0.02;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.9;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return -1;
    }

    int get_toxicity() override {
        return 0;
    }
};

