#pragma once


#include "../element.h"

class Mine: public Element {
public:
    const double FIREWORK = 1.0 / 12;

    void process(SandSimulation *sim, int row, int col) override {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (!sim->in_bounds(row + i, col + j)) {
                    continue;
                }
                int state = sim->elements[sim->get_cell(row + i, col + j)]->get_state();
                if (sim->is_on_fire(row, col) || !(state == 0 || state == -1)) {
                    for (int y = -9; y <= 9; y++) {
                        for (int x = -9; x <= 9; x++) {
                            if (y * y + x * x > 81) {
                                continue;
                            }
                            if (sim->in_bounds(row + y, col + x) ) {
                                sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 66 : 9);
                            }
                        }
                    }
                }
                return;
            }
        }
    }

    double get_density() override {
        return 16.0;
    }

    double get_explode_resistance() override {
        return 0.08;
    }

    double get_acid_resistance() override {
        return 0.65;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

