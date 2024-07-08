#pragma once


#include "../element.h"

class Osmium: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {

    }

    double get_density() override {
        return 128;
    }

    double get_explode_resistance() override {
        return 0.97;
    }

    double get_acid_resistance() override {
        return 0.97;
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

