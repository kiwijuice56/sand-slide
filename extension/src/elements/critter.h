#ifndef CRITTER_H
#define CRITTER_H

#include "element.h"
#include <stdlib.h>

class Critter: public Element {
public:
    const double FLAME = 1.0 / 128;
    const double JUMP = 1.0 / 8;
    const double MOVE = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        }

        bool on_ground = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) != 0;

        // Jumping
        if (randf() < JUMP && on_ground) {
            int dir = (std::rand() % 3) + 1;
            sim->move_and_swap(row, col, row - dir, col);
            return;
        }
        if (on_ground && randf() >= MOVE) {
            return;
        }
        int dir = (std::rand() % 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row + 1, col);
        }
    }

    double get_density() override {
        return 0.5;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.2;
    }
};

#endif // CRITTER_H