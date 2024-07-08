#pragma once


#include "../element.h"

class GlagglerSeed: public Element {
public:
    const double FLAME = 1 / 64.0;
    const double POWDER = 1 / 1.05;
    const double AWAKEN = 1 / 2048.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 20);
            return;
        }
        if (sim->randf() < AWAKEN) {
            for (int i = -4; i <= 4; i++) {
                for (int j = -3; j <= 4; j++) {
                    if (!sim->in_bounds(row + j, col + i)) {
                        continue;
                    }
                    if ((j == -3 || j == 4) && (i <= -3 || i >= 3)) {
                        continue;
                    }
                    if ((j == -2 || j == 3) && (i <= -4 || i >= 4)) {
                        continue;
                    }

                    if (j == -1 && (i == -1 || i == 1)) {
                        sim->set_cell(row + j, col + i, 176);
                        continue;
                    }
                    if (j == 1 && (i == -3 || i == 3)) {
                        sim->set_cell(row + j, col + i, 176);
                        continue;
                    }
                    if (j == 2 && (i >= -2 && i <= 2)) {
                        sim->set_cell(row + j, col + i, 176);
                        continue;
                    }
                    sim->set_cell(row + j, col + i, 177);
                }
            }
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
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.2;
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

