#pragma once


#include "../element.h"

class Thermostat: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.99;
    }

    double get_acid_resistance() override {
        return 0.99;
    }

    int get_state() override {
        return 0;
    }

    inline int fast_floor(double x) noexcept {
        return (int) x - (x < (int) x);
    }

    int get_temperature() override {
        double x = my_sim->time - fast_floor(my_sim->time);
        if (x < 1.0 / 2) {
            return 1;
        } else  {
            return -1;
        }
    }

    int get_toxicity() override {
        return 0;
    }
};

