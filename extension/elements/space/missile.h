#pragma once


#include "../element.h"

class Missile: public Element {
public:
    const double TRAIL = 1.0 / 16;
    const double EXPLODE = 1.0 / 2;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < TRAIL) {
            sim->grow(row + 1, col, 0, 69);
        }


        if (row == 0) {
            sim->set_cell(row, col, 0);
            return;
        }
        // Very long winded way of not allowing meteors to explode when touching meteor products
        if (sim->randf() < EXPLODE) {
            int x = sim->touch_count(row, col, 69) + sim->touch_count(row, col, 174) + sim->touch_count(row, col, 0) +
            sim->touch_count(row, col, 69) + sim->touch_count(row, col, 6) + sim->touch_count(row, col, 5) + sim->touch_count(row, col, 66) +
            sim->touch_count(row, col, 9) + sim->touch_count(row, col, 68) + sim->touch_count(row, col, 67);
            if (x < 8) {
                for (int y = -9; y <= 9; y++) {
                    for (int x = -9; x <= 9; x++) {
                        if (sim->in_bounds(row + y, col + x) && x * x + y * y < 81.0) {
                            sim->set_cell(row + y, col + x, sim->randf() < EXPLODE ? 66 : 9);
                        }
                    }
                }
            }
        }


        float closest_dist = 1000;
        int dir_x = 0;
        int dir_y = -1;
        for (int y = -32; y <= 32; y++) {
            for (int x = -32; x <= 32; x++) {
                if (sim->in_bounds(row + y, col + x) && can_target(sim, row + y, col + x)) {
                    float dist = y * y + x * x;
                    if (dist < closest_dist) {
                        dir_y = y < 0 ? -1 : (y == 0 ? 0 : 1);
                        dir_x = x < 0 ? -1 : (x == 0 ? 0 : 1);
                        closest_dist = dist;
                    }
                }
            }
        }
        sim->move_and_swap(row, col, row + dir_y, col + dir_x);
    }

    bool can_target(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86 || x == 164 || x == 158 || x == 150 || x == 167;
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.85;
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

