#ifndef ALGAE_GREEN_H
#define ALGAE_GREEN_H

#include "element.h"

class AlgaeGreen: public Element {
public:
    const double GROWTH = 1.0 / 2048;
    const double DEATH = 1.0 / 6000;
    const double FLAME = 1.0 / 48;

    void process(SandSimulation *sim, int row, int col) override {  
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        // Grow into water
        if (sim->randf() < GROWTH && sim->touch_count(row, col, 3) > 0) {
            sim->grow(row + (int) (sim->randf() * 3) - 1, col + (int) (sim->randf() * 3) - 1, 3, 7);
        }

        // Randomly decay to keep populations smaller
        if (sim->randf() < DEATH) {
            sim->set_cell(row, col, 3);
        } 
        
        if (sim->is_poisoned(row, col)) { 
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

#endif // ALGAE_GREEN_H