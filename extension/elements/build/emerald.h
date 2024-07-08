#pragma once




#include "../element.h"

class Emerald: public Element {
public:
    const double GROW = 1.0 / 2000;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= GROW) {
            return;
        }

        // We need to empty this cell for crystal branching checks
        sim->set_cell(row, col, 0);
        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0 && sim->cardinal_touch_count(row, col + dir, 80) == 0) {
            sim->grow(row, col + dir, 3, 80);
        } else if (sim->cardinal_touch_count(row - 1, col, 80) == 0) {
            sim->grow(row - 1, col, 3, 80);
        }
        sim->set_cell(row, col, 80);
    }

    double get_density() override {
        return 256.0;
    }

    double get_explode_resistance() override {
        return 0.99;
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

