#pragma once




#include "../element.h"

class Sandstone: public Element {
public:
    const double WEATHER = 1.0 / 2056;
    const double MELT = 1.0 / 1024;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < WEATHER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            sim->set_cell(row, col, 1);
        }
    }

    double get_density() override {
        return 5.0;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.45;
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

