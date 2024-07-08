#pragma once


#include "../element.h"
#include <stdlib.h>

class CoolLava: public Element {
public:
    const double MOVE = 1.0 / 2;
    const double COOL = 1.0 / 48;
    const double SPREAD = 1.0 / 42;
    const double DOWN_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 1.5;

    // Slightly slower than lava, spreading until it cools into obsidian
    void process(SandSimulation *sim, int row, int col) override {
        sim->liquid_process(row, col, 2);

        if (sim->randf() < COOL) {
            sim->set_cell(row, col, 57);
        } if (sim->randf() < SPREAD) {
            sim->grow(row + 1, col, 20, 56);
            sim->grow(row - 1, col, 20, 56);
            sim->grow(row, col - 1, 20, 56);
            sim->grow(row, col + 1, 20, 56);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.9;
    }

    double get_acid_resistance() override {
        return 0.99;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

