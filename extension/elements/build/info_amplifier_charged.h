#pragma once




#include "../element.h"

class InfoAmplifierCharged: public Element {
public:
    const double DECAY = 1.0 / 24;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 112);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int new_row = row + (sim->randf() < 0.435 ? 1 : -1);
            int new_col = col + 1;
            if (sim->in_bounds(new_row, new_col) && sim->get_cell(new_row, new_col) == 112) {
                sim->set_cell(new_row, new_col, 113);
                sim->set_cell(row, col, 112);
                row = new_row;
                col = new_col;
            }
        }
        if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) == 102) {
            sim->set_cell(row, col + 1, 103);
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

