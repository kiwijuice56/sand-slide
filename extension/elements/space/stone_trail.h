#pragma once


#include "../element.h"

class StoneTrail: public Element {
public:
    const double POWDER = 1 / 1.5;
    const double DECAY = 1.0 / 24;
    const double FLAME = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        }

        for (int i = -6; i <= 6; i++) {
            for (int j = -6; j <= 6; j++) {
                if (i * i + j * j > 36) {
                    continue;
                }
                if (can_infect(sim, row + i, col + j)) {
                    sim->set_cell(row + i, col + j, 2);
                }
            }
        }

        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 4.0;
    }

    double get_explode_resistance() override {
        return 0.4;
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

    bool can_infect(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86 || x == 158 || x == 150 || x == 167;
    }


    int get_toxicity() override {
        return 0;
    }
};

