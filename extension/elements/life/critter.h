#pragma once


#include "../element.h"
#include <stdlib.h>

// A land organism that jumps around randomly
class Critter: public Element {
public:
    const double FLAME = 1.0 / 32;
    const double POISON = 1.0 / 18;
    const double JUMP = 1.0 / 8;
    const double MOVE = 1.0 / 32;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        bool on_ground = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) != 0;

        // Jumping while on the floor
        if (sim->randf() < JUMP && on_ground) {
            int dir = (int) (sim->randf() * 3) - 1;
            sim->move_and_swap(row, col, row - dir, col);
            return;
        }

        // Moving horizontally
        if (on_ground && sim->randf() >= MOVE) {
            return;
        }
        int dir = (int) (sim->randf() * 3) - 1;
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
        return 0.5;
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

