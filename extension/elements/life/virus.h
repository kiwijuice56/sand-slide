#pragma once


#include "../element.h"

class Virus: public Element {
public:
    const double PROCESS = 1.0 / 32;
    const double DECAY = 1.0 / 1024;
    const double BURN = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
        }

        if (sim->randf() < BURN && (sim->is_on_fire(row, col) || sim->is_cold(row, col))) {
            sim->set_cell(row, col, 0);
        }

        // Adding a limit slows the infection down
        if (sim->randf() > PROCESS)
            return;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (can_infect(sim, row + i, col + j)) {
                    sim->set_cell(row + i, col + j, 101);
                    return;
                }
            }
        }

        int new_row = row + (sim->randf() < 0.5 ? 1 : -1);
        int new_col = col + (sim->randf() < 0.5 ? 1 : -1);

        sim->move_and_swap(row, col, new_row, new_col);
    }

    bool can_infect(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86 || x == 164 || x == 158 || x == 150 || x == 167;
    }


    double get_density() override {
        return 4.0;
    }

    double get_explode_resistance() override {
        return 0.3;
    }

    double get_acid_resistance() override {
        return 0.4;
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

