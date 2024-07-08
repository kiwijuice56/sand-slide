#pragma once




#include "../element.h"

class DrySponge: public Element {
public:
    const double GRAB = 1.0 / 16;
    const double PROCESS = 1.0 / 12;
    const double EAT = 1.0 / 4;
    const double WETTEN = 1.0 / 5;
    const double MOVE_WATER = 1.0 / 16;
    const double BURN = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < MOVE_WATER) {
            int new_row = row + (sim->randf() < 0.5 ? 1 : -1);
            int new_col = col + (sim->randf() < 0.5 ? 1 : -1);
            if (sim->in_bounds(new_row, new_col) && sim->get_cell(new_row, new_col) == 100) {
                sim->set_cell(new_row, new_col, 99);
                sim->set_cell(row, col, 100);
                return;
            }
        }

        if (sim->randf() < BURN && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() >= PROCESS)
            return;

        for (int y = row - 3; y <= row + 3; y++) {
            for (int x = col - 3; x <= col + 3; x++) {
                if (sim->randf() < EAT && (sim->in_bounds(y, x) && (sim->get_cell(y, x) == 3 || sim->get_cell(y, x) == 59 || sim->get_cell(y, x) == 71))) {
                    sim->set_cell(y, x, 0);
                    if (sim->randf() < WETTEN) {
                        sim->set_cell(row, col, 100);
                        return;
                    }
                }
            }
        }

        if (sim->cardinal_touch_count(row, col, 0) == 0)
            return;

        for (int y = row - 6; y <= row + 6; y++) {
            for (int x = col - 6; x <= col + 6; x++) {
                if (sim->randf() >= GRAB || !(sim->in_bounds(y, x) && (sim->get_cell(y, x) == 3 || sim->get_cell(y, x) == 59 || sim->get_cell(y, x) == 71)))
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
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.95;
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

