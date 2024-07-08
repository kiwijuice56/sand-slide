#pragma once


#include "../element.h"

// A salt water fish that shifts left and right through water
// Left and right varities are the same, but are used to move fish in both directions
class FishRight: public Element {
public:
    const double GROWTH = 1.0 / 256;
    const double DEATH = 1.0 / 1600;
    const double POISON = 1.0 / 16;
    const double PROCESS = 1.0 / 4;
    const double VERTICAL = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() > PROCESS) {
            return;
        }

        if (sim->randf() < GROWTH) {
            sim->grow(row - 1, col, 71, 73);
            return;
        } else if (sim->randf() < DEATH) {
            sim->set_cell(row, col, 71);
            return;
        }

        if (sim->touch_count(row, col, 71) <= 2) {
            sim->set_cell(row, col, 0);
            return;
        }

        if (sim->randf() < POISON && (sim->is_poisoned(row, col) || sim->touch_count(row, col, 3))) {
            sim->set_cell(row, col, 16);
            return;
        }

        if (sim->randf() < VERTICAL) {
            sim->move_and_swap(row, col, row + (sim->randf() < 0.5 ? 1 : -1), col);
        } else if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) == 71) {
            sim->move_and_swap(row, col, row, col + 1);
        } else {
            sim->set_cell(row, col, 72);
        }
    }

    double get_density() override {
        return 2.5;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.35;
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

