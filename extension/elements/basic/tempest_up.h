#pragma once


#include "../element.h"

class TempestUp: public Element {
public:
    const double DECAY = 1.0 / 512;
    const double FLAME = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        } if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
        }
        if (row == 0) {
            sim->set_cell(row, col, 146);
            return;
        }

        int newRow = row - 1;
        int newCol = col + (int) (sim->randf() * 3) - 1;

        if (sim->in_bounds(newRow, newCol) && (sim->get_cell(newRow, newCol) == 146 || sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 800.0)) {
            sim->set_cell(row, col, sim->get_cell(newRow, newCol));
            sim->set_cell(newRow, newCol, 147);
        }
    }

    double get_density() override {
        return 800.0;
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

