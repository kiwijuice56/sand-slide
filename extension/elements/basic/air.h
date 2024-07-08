#pragma once


#include "../element.h"

class Air: public Element {
public:
    const double DECAY = 1.0 / 300;
    const double MOVE = 1.0 / 1.09;
    const double FLAME = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        } if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
        }

        int newRow = row + (int) (sim->randf() * 3) - 1;
        int newCol = col + (int) (sim->randf() * 3) - 1;

        if (sim->randf() < MOVE && sim->in_bounds(newRow, newCol) &&
        sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 65.0) {
            sim->set_cell(row, col, sim->get_cell(newRow, newCol));
            sim->set_cell(newRow, newCol, 28);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.1;
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

