#pragma once


#include "../element.h"

class FlowerPetalC: public Element {
public:
    const double FLAME = 1.0 / 4;
    const double POISON = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.2;
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

