#pragma once


#include "../element.h"

class Alien: public Element {
public:
    const double GROWTH = 0.0049625;
    const double DISSOLVE = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        sim->grow(row + 1, col, 0, 150);
        sim->grow(row - 1, col, 0, 150);
        sim->grow(row, col + 1, 0, 150);
        sim->grow(row, col - 1, 0, 150);
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.55;
    }

    double get_acid_resistance() override {
        return 0.85;
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

