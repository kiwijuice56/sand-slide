#ifndef ALGAE_H
#define ALGAE_H

#include "element.h"

class Algae: public Element {
public:
    const double GROWTH = 1.0 / 2048;
    const double DEATH = 1.0 / 6000;
    const double FLAME = 1.0 / 48;

    void process(SandSimulation *sim, int row, int col) override {  
        // Catch on fire
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        // Grow into water
        if (randf() < GROWTH && sim->touch_count(row, col, 3) > 0) {
            sim->grow(row + (std::rand() % 2) - 1, col + std::rand() % 2 - 1, 3, 7);
        }
        else if (randf() < DEATH) {
            sim->set_cell(row, col, 3);
        } else if (sim->is_poisoned(row, col)) {
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

#endif // ALGAE_H