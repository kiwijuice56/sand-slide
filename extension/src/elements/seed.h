#ifndef SEED_H
#define SEED_H

#include "element.h"

class Seed: public Element {
public:
    const double DECAY = 1.0 / 8000;
    const double GERMINATE = 1.0 / 1024;
    const double FLAME = 1.0 / 48;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        sim->move_and_swap(row, col, row + 1, col);

        // Turn into a germinated seed
        if (randf() < DECAY) {
            sim->set_cell(row, col, 11);
        } else if (randf() < GERMINATE && sim->touch_count(row, col, 3) > 0) {
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