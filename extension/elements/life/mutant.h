#pragma once


#include "../element.h"
#include <stdlib.h>

class Mutant: public Element {
public:
    const double FLAME = 1.0 / 16;
    const double POISON = 1.0 / 8;
    const double JUMP = 1.0 / 8;
    const double MOVE = 1.0 / 24;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (can_kill(sim, row + i, col + j)) {
                    sim->set_cell(row + i, col + j, 16);
                }
            }
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

    bool can_kill(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86;
    }

    double get_density() override {
        return 0.5;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.8;
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

