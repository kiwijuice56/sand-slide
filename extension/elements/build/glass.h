#pragma once




#include "../element.h"

class Glass: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {

    }

    double get_density() override {
        return 3.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.95;
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

