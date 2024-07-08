#pragma once


#include "../element.h"

class PowderB: public Element {
public:
    const double FLAME = 1 / 32.0;
    const double DISSOLVE = 1 / 256.0;
    const double POWDER = 1 / 1.125;

    // Duplicate of PowderA
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER){
            return;
        }
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        } else if (sim -> randf() < DISSOLVE && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 43);
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

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.7;
    }

    double get_acid_resistance() override {
        return 0.6;
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

