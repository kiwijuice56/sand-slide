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
};

#endif // SAND_H