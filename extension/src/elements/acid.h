#ifndef ACID_H
#define ACID_H

#include "element.h"
#include <stdlib.h>

class Acid: public Element {
public:
    const double DECAY = 1.0 / 1024;
    const double EAT = 1.0 / 8;
    const double EMIT = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        // Decay
        if (randf() < DECAY && sim->touch_count(row, col, 0) > 0) {
            sim->set_cell(row, col, 22);
            return;
        }

        int dir = (std::rand() % 3) - 1;
        int newCol = col;
        int newRow = row;
        if (dir != 0) {
            newCol += dir;
        } else {
            newRow++;
        }

        // Ensure that the swallowed cell is in bounds and not acid
        if (!sim->in_bounds(newRow, newCol))
            return;
        if (sim->get_cell(newRow, newCol) == 21) 
            return;

        // Swap and delete
        if (sim->get_cell(newRow, newCol) == 0 || randf() < EAT * (1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_acid_resistance())) {
            sim->move_and_swap(row, col, newRow, newCol);
            sim->set_cell(row, col, 0);
        }

        if (randf() < EMIT) {
            sim->grow(row - 1, col, 0, 22);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // ACID_H