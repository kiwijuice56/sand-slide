#ifndef ALGAE_BROWN_H
#define ALGAE_BROWN_H

#include "element.h"

class AlgaeBrown: public Element {
public:
    const double GROWTH = 1.0 / 2048;
    const double DEATH = 1.0 / 6000;
    const double FLAME = 1.0 / 48;
    const double POISON = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {  
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        // Grow into water
        if (sim->randf() < GROWTH) {
            sim->grow(row + (int) (sim->randf() * 3) - 1, col + (int) (sim->randf() * 3) - 1, 3, 55);
            sim->grow(row + (int) (sim->randf() * 3) - 1, col + (int) (sim->randf() * 3) - 1, 71, 55);
        }

        // Randomly decay to keep populations smaller
        if (sim->randf() < DEATH) {
            sim->set_cell(row, col, sim->touch_count(row, col, 71) > sim->touch_count(row, col, 3) ? 71 : 3);
        } 
        
        if (sim->randf() < POISON && sim->is_poisoned(row, col)) { 
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // ALGAE_BROWN_H