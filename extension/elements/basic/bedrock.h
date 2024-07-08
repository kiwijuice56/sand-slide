#pragma once


#include "../element.h"

class Bedrock: public Element {
public:
    const double WEATHER = 1.0 / 4096;
    const double MELT = 1.0 / 4096;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < WEATHER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            sim->set_cell(row, col, 2);
        } else if (sim->randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 20);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.995;
    }

    double get_acid_resistance() override {
        return 0.995;
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

