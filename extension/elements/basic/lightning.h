#pragma once


#include "../element.h"

class Lightning: public Element {
public:
    const double DOWN = 1 / 1.20;

    void process(SandSimulation *sim, int row, int col) override {
        int n_count = sim->touch_count(row, col, 0) + sim->touch_count(row, col, 37) +
        sim->touch_count(row, col, 6) + sim->touch_count(row, col, 22);
        if (n_count != 8) {
            sim->set_cell(row, col, 38);
        } else {
            for (int i = 0; i < 1; i++) {
                if (!sim->in_bounds(row, col))
                    return;
                int rand_row = row + (sim->randf() < DOWN ? 1 : -1);
                int rand_col = col + (int) (sim->randf() * 3) - 1;
                sim->set_cell(row, col, 0);
                if (sim->touch_count(rand_row, rand_col, 37) <= 1) {
                    sim->grow(rand_row, rand_col, 0, 37);
                    sim->grow(rand_row, rand_col, 6, 37);
                    sim->grow(rand_row, rand_col, 22, 37);
                }
                sim->set_cell(row, col, 37);
                row = rand_row;
                col = rand_col;
            }
        }
    }

    double get_density() override {
        return 0.01;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.2;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

