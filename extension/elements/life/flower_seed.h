#pragma once


#include "../element.h"

class FlowerSeed: public Element {
public:
    const double DECAY = 1.0 / 8000;
    const double GERMINATE = 1.0 / 800;
    const double FLAME = 1.0 / 48;
    const double POWDER = 1 / 1.125;
    const double POISON = 1.0 / 16;
    const double GRASS = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;

        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        // Turn into a germinated seed when watered, but wither out after a while
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 11);
            return;
        }

        if (sim->randf() < GERMINATE && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, sim->randf() < GRASS ? 13 : 120);
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
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
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

