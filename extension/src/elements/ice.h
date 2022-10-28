#ifndef ICE_H
#define ICE_H

class SandSimulation;

#include "element.h"

class Ice: public Element {
public:
    const double GROW = 1.0 / 6000;
    const double FLAME = 1.0 / 800;

    void process(SandSimulation *sim, int row, int col) override {
        // Melt
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 3);
            return;
        }

        if (randf() >= GROW) {
            return;
        }

        // We need to empty this cell for ice branching checks
        sim->set_cell(row, col, 0);
        int dir = (std::rand() % 3) - 1;
        if (dir != 0 && sim->cardinal_touch_count(row, col + dir, 19) == 0) {
            sim->grow(row, col + dir, 3, 19);
        } else if (sim->cardinal_touch_count(row + 1, col, 19) == 0) {
            sim->grow(row + 1, col, 3, 19);
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
};

#endif // ICE_H