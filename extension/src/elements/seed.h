#ifndef SEED_H
#define SEED_H

#include "element.h"

class Seed: public Element {
public:
    const double DECAY = 1.0 / 8000;
    const double GERMINATE = 1.0 / 1024;
    const double FLAME = 1.0 / 48;
    const double POWDER = 1 / 1.125;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;

        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        } else if (sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        sim->move_and_swap(row, col, row + 1, col);

        // Turn into a germinated seed
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 11);
        } else if (sim->randf() < GERMINATE && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 13);
        } 
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // SEED_H