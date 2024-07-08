#pragma once


#include "../element.h"

class Fire: public Element {
public:
    const double DECAY = 1.0 / 90;
    const double EVAPORATE = 1.0 / 5;

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
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 6);
        }

        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 0.45;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
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

