#pragma once




#include "../element.h"

class InfoDeleterCharged: public Element {
public:
    const double DELETE = 1.0 / 32;
    const double DELETE_SINGLE = 1.0 / 1.25;
    const double LOSE_CHARGE = 1.0 / 3;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < LOSE_CHARGE) {
            sim->set_cell(row, col, 107);
            return;
        }
        if (sim->randf() < DELETE) {
            for (int y = -8; y <= 8; y++) {
                for (int x = -8; x <= 8; x++) {
                    if (sim->randf() < DELETE_SINGLE) {
                        continue;
                    }
                    if (y * y + x * x > 48) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x)) {
                        int c = sim->get_cell(row + y, col + x);
                        if (c == 0 || c == 104 || c == 15 || c == 107 || c == 102 || c == 103 || c == 108 || c == 6 || c == 111 || c == 112 || c == 113)
                            continue;
                        sim->set_cell(row + y, col + x, 108);
                    }
                }
            }
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.99;
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

