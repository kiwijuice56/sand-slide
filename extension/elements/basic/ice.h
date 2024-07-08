#pragma once


#include "../element.h"

class Ice: public Element {
public:
    const double GROW = 1.0 / 1700;
    const double FLAME = 1.0 / 128;

    void process(SandSimulation *sim, int row, int col) override {
        // Melt
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 3);
            return;
        }

        if (sim->randf() >= GROW) {
            return;
        }

        // We need to empty this cell for ice branching checks
        sim->set_cell(row, col, 0);
        int dir = (int) (sim->randf() * 3) - 1;
        if (dir != 0 && sim->cardinal_touch_count(row, col + dir, 19) + sim->cardinal_touch_count(row, col + dir, 65) == 0) {
            sim->grow(row, col + dir, 3, 19);
            sim->grow(row, col + dir, 71, 19);
        } else if (sim->cardinal_touch_count(row + 1, col, 19) + sim->cardinal_touch_count(row + 1, col, 65) == 0) {
            sim->grow(row + 1, col, 3, 19);
            sim->grow(row + 1, col, 71, 19);
        }
        sim->set_cell(row, col, 19);
    }

    double get_density() override {
        return 1.1;
    }

    double get_explode_resistance() override {
        return 0.35;
    }

    double get_acid_resistance() override {
        return 0.9;
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

