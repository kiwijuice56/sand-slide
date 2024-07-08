#pragma once


#include "../element.h"

class QuickSand: public Element {
public:
    const double GRAB = 1.0 / 32;
    const double PROCESS = 1.0 / 64;
    const double ABSORB = 1.0 / 4;
     const double POWDER = 1 / 1.05;


    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;
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

        if (sim->randf() > PROCESS) {
            return;
        }
        // Absorb anything in immediate proximity if not a black hole
        for (int y = row - 1; y <= row; y++) {
            for (int x = col - 1; x <= col + 1; x++) {
                if (sim->in_bounds(y, x) && sim->get_cell(y, x) != 156 && sim->get_cell(y, x) != 15) {
                    sim->set_cell(y, x, 0);
                }
            }
        }

        // If the black hole has no space around it after absorbing all 4 directions,
        // it is in the middle of the black hole and doesn't need to keep processing
        if (sim->cardinal_touch_count(row, col, 0) == 0) {
            return;
        }

        // Keep moving particles closer into the black hole
        for (int y = row - 4; y <= row + 4; y++) {
            for (int x = col - 4; x <= col + 4; x++) {
                if (sim->randf() >= GRAB || !sim->in_bounds(y, x) || sim->get_cell(y, x) == 156)
                    continue;

                int dirRow = row - y < 0 ? -1 : 1;
                int dirCol = col - x < 0 ? -1 : 1;
                if (row == y) dirRow = 0;
                if (col == x) dirCol = 0;
                sim->move_and_swap(y, x, y + dirRow, x + dirCol);
            }
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

