#ifndef SAND_H
#define SAND_H

#include "element.h"

class Sand: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.2;
    }
};

#endif // SAND_H