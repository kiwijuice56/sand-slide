#ifndef ICE_BOMB_H
#define ICE_BOMB_H

class SandSimulation;

#include "element.h"

class IceBomb: public Element {
public:
    const double FLAME = 0.05;
    const double FIREWORK = 1.0 / 8;
    const double DECAY = 1.0 / 1024;
    const double GROW = 1.0 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 96);
            return;
        }
        if (sim->randf() < GROW) {
            sim->grow(row + 1, col, 0, 96);
            sim->grow(row - 1, col, 0, 96);
            sim->grow(row, col + 1, 0, 96);
            sim->grow(row, col - 1, 0, 96);
        }

        // Explode
        if (sim->randf() < FLAME && sim->touch_count(row, col, 88) + sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, sim->randf() < FIREWORK ? 90 : 88);
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
};

#endif // ICE_BOMB_H