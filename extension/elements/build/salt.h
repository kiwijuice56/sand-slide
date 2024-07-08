#pragma once


#include "../element.h"

class Salt: public Element {
public:
    const double POWDER = 1 / 1.02;
    const double MIX = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < MIX && sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 71);
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

    double get_density() override {
        return 1.025;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.9;
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

