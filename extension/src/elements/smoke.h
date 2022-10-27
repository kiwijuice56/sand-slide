#ifndef SMOKE_H
#define SMOKE_H

#include "element.h"

class Smoke: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        if (std::rand() % 128 == 0) {
            sim->set_cell(row, col, 0);
        }

        int dir = (std::rand() % 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 0.35;
    }
};

#endif // SMOKE_H