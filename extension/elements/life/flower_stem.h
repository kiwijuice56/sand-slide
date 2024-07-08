#pragma once


#include "../element.h"

class FlowerStem: public Element {
public:
    const double GROW = 1.0 / 212;
    const double FLOWER = 1.0 / 1024;
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
            sim->grow(row - 1, col, 0, 121);
            sim->grow(row - 1, col, 3, 121);
            sim->grow(row - 1, col, 11, 121); // Soil
            sim->grow(row - 1, col, 12, 121); // Grass things
            sim->grow(row - 1, col, 13, 121);
            sim->grow(row - 1, col, 119, 121); // Flower things
            sim->grow(row - 1, col, 120, 121);
        } else if (sim->randf() < FLOWER && sim->in_bounds(row - 1, col)  &&
        !(sim->get_cell(row - 1, col) >= 119 && sim->get_cell(row - 1, col) <= 125)) {
            sim->set_cell(row, col, 122);
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

