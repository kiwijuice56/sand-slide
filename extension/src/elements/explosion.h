#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "element.h"

class Explosion: public Element {
public:
    const double PROCESS = 1.0 / 4;
    const double DECAY = 1.0 / 11;
    const double EXTINGUISH = 1.0 / 1.5;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the explosion down
        if (sim->randf() > PROCESS) {
            return;
        } else if (sim->randf() < EXTINGUISH && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) >= 1) {
            sim->set_cell(row, col, 6);
        // We eliminate explosions that reach the end, as they tend to linger for a long time if not checked
        } else if (sim->randf() < DECAY || sim->touch_count(row, col, 6) > 1 ||
            row == sim->get_height() - 1 || col == sim->get_width() - 1 || col == 0 || row == 0) {
            sim->set_cell(row, col, 6);
        } else {
            sim->grow(row + 1, col, -1, 9);
            sim->grow(row - 1, col, -1, 9);
            sim->grow(row, col + 1, -1, 9);
            sim->grow(row, col - 1, -1, 9);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.0;
    }

    double get_acid_resistance() override {
        return 0.0;
    }
};

#endif // EXPLOSION_H