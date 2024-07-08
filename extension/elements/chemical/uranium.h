#pragma once


#include "../element.h"

class Uranium: public Element {
public:
    const double FLAME = 0.05;

    void process(SandSimulation *sim, int row, int col) override {
        // Explode
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 34);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.08;
    }

    double get_acid_resistance() override {
        return 0.65;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

