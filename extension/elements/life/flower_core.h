#pragma once


#include "../element.h"

class FlowerCore: public Element {
public:
    const double GROW = 1.0 / 64;
    const double FLAME = 1.0 / 16;
    const double LEFT = 0.1;
    const double RIGHT = 0.2;
    const double POISON = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        if (sim->randf() < GROW) {
            int petal = 123 + int(sim->randf() * 3.0);

            sim->grow(row - 1, col, 0, petal);
            sim->grow(row + 1, col, 0, petal);
            sim->grow(row, col - 1, 0, petal);
            sim->grow(row, col + 1, 0, petal);

            sim->grow(row - 1, col, 3, petal);
            sim->grow(row + 1, col, 3, petal);
            sim->grow(row, col - 1, 3, petal);
            sim->grow(row, col + 1, 3, petal);

            sim->grow(row - 1, col, 121, petal);
            sim->grow(row + 1, col, 121, petal);
            sim->grow(row, col - 1, 121, petal);
            sim->grow(row, col + 1, 121, petal);
        }
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
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

