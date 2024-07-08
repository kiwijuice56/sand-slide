#pragma once




#include "../element.h"

class InfoDeleter: public Element {
public:
    const double DELETE = 1.0 / 32;
    const double DELETE_SINGLE = 1.0 / 1.25;

    void process(SandSimulation *sim, int row, int col) override {
        for (int i = 0; i < 4; i++) {
            int new_row = row + (sim->randf() < 0.435 ? 1 : -1);
            int new_col = col + (sim->randf() < 0.5 ? 1 : -1);
            if (sim->in_bounds(new_row, new_col) && sim->get_cell(new_row, new_col) == 111) {
                sim->set_cell(new_row, new_col, 107);
                sim->set_cell(row, col, 111);
                row = new_row;
                col = new_col;
            }
        }
        if (sim->touch_count(row, col, 104) + sim->touch_count(row, col, 103) + sim->touch_count(row, col, 113) > 0) {
            sim->set_cell(row, col, 111);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.99;
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

