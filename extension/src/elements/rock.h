#ifndef ROCK_H
#define ROCK_H

class SandSimulation;

#include "element.h"

class Rock: public Element {
public:
    const double WEATHER = 1.0 / 2056;

    void process(SandSimulation *sim, int row, int col) override {
        if (randf() < WEATHER && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 11);
        }
    }

    double get_density() override {
        return 5.0;
    }
};

#endif // ROCK_H