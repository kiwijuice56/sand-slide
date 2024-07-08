#pragma once


#include "../element.h"
#include <stdlib.h>

class BlackSlime: public Element {
public:
    const double FLAME = 1.0 / 8;
    const double GROW = 1.0 / 16;
    const double CLIMB = 1.0 / 128;
    const double MELT = 1.0 / 128;
    const double SLIME = 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        }

        float x = sim->time - fast_floor(sim->time);
        if (x < 0.5) {
            sim->liquid_process(row, col, 2);
        } else if (sim->randf() < GROW) {
            sim->grow(row - 1, col, 0, 167);
        }
    }

    inline int fast_floor(double x) noexcept {
        return (int) x - (x < (int) x);
    }

    double get_density() override {
        return 4.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.999;
    }

    int get_state() override {
        double x = my_sim->time - fast_floor(my_sim->time);
        if (x < 0.5) {
            return 1;
        } else  {
            return 0;
        }
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

