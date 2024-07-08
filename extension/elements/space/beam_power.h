#pragma once


#include "../element.h"

class BeamPower: public Element {
public:
    const double DOWN = 1 / 1.1;

    void process(SandSimulation *sim, int row, int col) override {
        int n_count = sim->touch_count(row, col, 0) + sim->touch_count(row, col, 114) +
        sim->touch_count(row, col, 6) + sim->touch_count(row, col, 22);
        if (n_count != 8) {
            sim->set_cell(row, col, 115);
        } else {
            for (int i = 0; i < 4; i++) {
                if (!sim->in_bounds(row, col))
                    return;
                int rand_row = row - (sim->randf() < DOWN ? 1 : -1);
                int rand_col = col + (int) (sim->randf() * 3) - 1;
                if (sim->get_cell(row, col) != 15) {
                    sim->set_cell(row, col, 0);
                }
                if (sim->touch_count(rand_row, rand_col, 114) <= 1) {
                    sim->grow(rand_row, rand_col, 0, 114);
                    sim->grow(rand_row, rand_col, 6, 114);
                    sim->grow(rand_row, rand_col, 22, 114);
                }
                if (sim->get_cell(row, col) != 15) {
                    sim->set_cell(row, col, 114);
                }
                row = rand_row;
                col = rand_col;
            }
        }
    }

    double get_density() override {
        return 0.05;
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
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

