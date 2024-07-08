#pragma once


#include "../element.h"

class DracoMeteorA: public Element {
public:
    const double HORIZONTAL = 1.0 / 12;
    const double TRAIL = 1.0 / 9;
    const double EXPLODE = 1.0 / 2;
    const double PROCESS = 1.0 / 1.01;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < TRAIL) {
            sim->grow(row + 1, col, 0, 145);
        }

        // Very long winded way of not allowing meteors to explode when touching meteor products
        if (sim->randf() < EXPLODE && (
        !sim->in_bounds(row + 1, col)
        || sim->get_cell(row + 1, col) != 69 && sim->get_cell(row + 1, col) != 137 && sim->get_cell(row + 1, col) != 138
        && sim->get_cell(row + 1, col) != 139  && sim->get_cell(row + 1, col) != 0 && sim->get_cell(row + 1, col) != 9
        && sim->get_cell(row + 1, col) != 46  && sim->get_cell(row + 1, col) != 5  && sim->get_cell(row + 1, col) != 47  && sim->get_cell(row + 1, col) != 48
        && sim->get_cell(row + 1, col) != 6 && sim->get_cell(row + 1, col) != 24 && sim->get_cell(row + 1, col) != 140
        && sim->get_cell(row + 1, col) != 141 && sim->get_cell(row + 1, col) != 142 && sim->get_cell(row + 1, col) != 143
        && sim->get_cell(row + 1, col) != 144 && sim->get_cell(row + 1, col) != 145)) {
            for (int y = -16; y <= 16; y++) {
                for (int x = -16; x <= 16; x++) {
                    if (sim->in_bounds(row + y, col + x) && x * x + y * y < 256.0) {
                        sim->set_cell(row + y, col + x, sim->randf() < EXPLODE ? 140 : 0);
                    }
                }
            }
            return;
        }

        if (sim->randf() < HORIZONTAL) {
            sim->move_and_swap(row, col, row + 1, col + (sim->randf() < 0.5 ? 1 : -1));
        } else {
            sim->move_and_swap(row, col, row + 1, col);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.85;
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

