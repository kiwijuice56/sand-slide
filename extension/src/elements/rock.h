#ifndef ROCK_H
#define ROCK_H

class SandSimulation;

#include "element.h"

class Rock: public Element {
public:
    const double WEATHER = 1.0 / 2056;
    const double MELT = 1.0 / 1024;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < WEATHER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            sim->set_cell(row, col, 11);
        } else if (sim->randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 20);
        }
    }

    double get_density() override {
        return 5.0;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.45;
    }
};

#endif // ROCK_H