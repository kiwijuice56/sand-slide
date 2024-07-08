#pragma once


#include "../element.h"

class FrozenAcid: public Element {
public:
    const double GROW = 1.0 / 256;
    const double FLAME = 1.0 / 128;

    void process(SandSimulation *sim, int row, int col) override {
        // Melt
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 21);
            return;
        }

        if (sim->randf() >= GROW) {
            return;
        }

        // We need to empty this cell for ice branching checks
        sim->set_cell(row, col, 0);
        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0 && sim->cardinal_touch_count(row, col + dir, 154) == 0) {
            sim->grow(row, col + dir, 21, 154);
            sim->grow(row, col + dir, 59, 154);
        } else if (sim->cardinal_touch_count(row + 1, col, 154) == 0) {
            sim->grow(row + 1, col, 21, 154);
            sim->grow(row + 1, col, 59, 154);
        }
        sim->set_cell(row, col, 154);
    }

    double get_density() override {
        return 1.1;
    }

    double get_explode_resistance() override {
        return 0.35;
    }

    double get_acid_resistance() override {
        return 1.0;
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

