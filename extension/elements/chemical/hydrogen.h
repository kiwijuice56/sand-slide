#pragma once


#include "../element.h"

class Hydrogen: public Element {
public:
    const double DECAY = 1.0 / 700;
    const double UP = 1.0 / 1.5;
    const double UP_BLOCK = 1.0 / 16;
    const double EXPLODE = 1.0 / 8;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
        }
        if (sim->randf() < EXPLODE && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 48);
        }

        bool blocked = !sim->in_bounds(row - 1, col) || sim->get_cell(row - 1, col) == 6;
        if (sim->randf() < (blocked ? UP_BLOCK : UP)) {
            sim->move_and_swap(row, col, row - 1, col);
        } else {
            sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
        }
    }

    double get_density() override {
        return 0.05;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.1;
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

