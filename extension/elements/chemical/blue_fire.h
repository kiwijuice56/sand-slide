#pragma once


#include "../element.h"

class BlueFire: public Element {
public:
    const double DECAY = 1.0 / 128;
    const double UP = 1.0 / 1.5;
    const double UP_BLOCK = 1.0 / 16;
    const double DOWN = 1.0 / 4;
    const double EVAPORATE = 1.0 / 3;

    void process(SandSimulation *sim, int row, int col) override {
        // Evaporate nearby water, since smoke tends to put distance between fire and water
        if (sim->randf() < EVAPORATE) {
            for (int y = row - 1; y <= row + 1; y++) {
                for (int x = col - 1; x <= col + 1; x++) {
                    if (sim->in_bounds(y, x) && (sim->get_cell(y, x) == 3 || sim->get_cell(y, x) == 71)) {
                        sim->set_cell(y, x, 58);
                    }
                }
            }
        }

        // Extinguish
        if (sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            sim->set_cell(row, col, 58);
            return;
        }

        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 6);
        }

        bool blocked = !sim->in_bounds(row - 1, col) || sim->get_cell(row - 1, col) == 24;
        if (sim->randf() < (blocked ? UP_BLOCK : UP)) {
            sim->move_and_swap(row, col, row - 1, col);
        } else {
            sim->move_and_swap(row, col, row + (sim->randf() < DOWN ? 0 : 1), col + (sim->randf() < 0.5 ? 1 : -1));
        }
    }

    double get_density() override {
        return 0.45;
    }

    double get_explode_resistance() override {
        return 0.25;
    }

    double get_acid_resistance() override {
        return 0.25;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

