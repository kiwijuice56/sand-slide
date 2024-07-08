#pragma once


#include "../element.h"
#include <stdlib.h>

class Dust: public Element {
public:
    const double FLAME = 1.0 / 64;
    const double PROCESS = 1.0 / 2;
    const double FLY = 1.0 / 1.5;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }
        if (sim->randf() < FLY && sim->touch_count(row, col, 28) > 0) {
            sim->move_and_swap(row, col, row - 2, col);
        }

        if (sim->randf() > PROCESS || !sim->in_bounds(row + 1, col))
            return;
        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0)
            sim->move_and_swap(row, col, row, col + dir);
        else
            sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 0.96;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
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

