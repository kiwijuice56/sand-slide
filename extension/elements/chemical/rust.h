#pragma once


#include "../element.h"

class Rust: public Element {
public:
    const double POWDER = 1 / 1.15;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 1.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 1.0;
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

