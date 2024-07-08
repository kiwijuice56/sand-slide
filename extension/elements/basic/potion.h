#pragma once


#include "../element.h"

class Potion: public Element {
public:
    const double ABSORB = 1.0 / 4098;
    const double MELT = 1.0 / 128;
    const double EVAPORATION = 1.0 / 512;
    const double MIX = 1.0 / 32;
    const double FREEZE = 1.0 / 1024;

    void process(SandSimulation *sim, int row, int col) override {
        double random = sim->randf();
        // Absorption into plants
        if (random < ABSORB && sim->cardinal_touch_count(row, col, 14) > 0) {
            sim->set_cell(row, col, 0);
            return;
        }

        // Conductivity
        if (random < MELT && (sim->cardinal_touch_count(row, col, 38) > 0 || sim->cardinal_touch_count(row, col, 40) > 0 || sim->cardinal_touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 163, 38);
            sim->grow(row - 1, col, 163, 38);
            sim->grow(row, col - 1, 163, 38);
            sim->grow(row, col + 1, 163, 38);
            return;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (can_infect(sim, row + i, col + j)) {
                    sim->set_cell(row + i, col + j, 27);
                    return;
                }
            }
        }

        sim->liquid_process(row, col, 2);
    }

    double get_density() override {
        if (my_sim->randf() < 0.5) {
            return my_sim->randf() * 1.0;
        }
        return my_sim->randf() * 64;
    }

    bool can_infect(SandSimulation *sim, int row, int col) {
        if (!sim->in_bounds(row, col))
            return false;
        int x = sim->get_cell(row, col);
        return x == 4 || x == 7 || x == 8 || x == 12 || x == 13 || x == 14 || x == 23 || x == 31 || x == 167
        || x == 32 || x == 33 || x == 49 || x == 54 || x == 55 || x == 72 || x == 73 || x == 86 || x == 164 || x == 158;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.95;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return my_sim->randf() < 0.99999 ? (0) : (my_sim->randf() < 0.5 ? -1 : 1);
    }

    int get_toxicity() override {
        return my_sim->randf() < 0.99 ? (0) : 1;
    }
};

