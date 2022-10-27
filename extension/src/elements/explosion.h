#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "element.h"

class Explosion: public Element {
public:
    const double PROCESS = 1.0 / 24;
    const double GROW = 1.0 / 8;
    const double DECAY = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (randf() > PROCESS) {
            return;
        }
        if (randf() < DECAY || sim->touch_count(row, col, 6) > 0) {
            sim->set_cell(row, col, 6);
        } else if (randf() < GROW) {
            sim->grow(row + 1, col, -1, 9);
            sim->grow(row - 1, col, -1, 9);
            sim->grow(row, col + 1, -1, 9);
            sim->grow(row, col - 1, -1, 9);
        }
    }

    double get_density() override {
        return 32.0;
    }
};

#endif // EXPLOSION_H