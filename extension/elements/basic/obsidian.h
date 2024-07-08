#pragma once




#include "../element.h"

class Obsidian: public Element {
public:
    const double MELT = 1.0 / 2048;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 20);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.9;
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

