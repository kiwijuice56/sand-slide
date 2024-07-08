#pragma once


#include "../element.h"

class Joy: public Element {
public:
    const double FLAME = 1 / 64.0;
    const double POWDER = 1 / 1.09;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        bool dead  = false;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (can_infect(sim, row + i, col + j)) {
                    sim->set_cell(row, col, 0);
                    sim->set_cell(row + i, col + j, 158);
                    dead = true;
                }
            }
        }
        if (dead) {
            return;
        }

        bool bot_left = sim->is_swappable(row, col, row + 1, col - 1);
        bool bot = sim->is_swappable(row, col, row + 1, col);
        bool bot_right = sim->is_swappable(row, col, row + 1, col + 1);
        if (bot) {
            sim->move_and_swap(row, col, row + 1, col);
        } else if (bot_left && bot_right) {
            sim->move_and_swap(row, col, row + 1, col + (sim->randf() < 0.5 ? 1 : -1));
        } else if (bot_left) {
            sim->move_and_swap(row, col, row + 1, col - 1);
        } else if (bot_right) {
            sim->move_and_swap(row, col, row + 1, col + 1);
        }
    }

    bool can_infect(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31 || x == 167
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86 || x == 164 || x == 158;
    }

    double get_density() override {
        return 1.0;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.1;
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

