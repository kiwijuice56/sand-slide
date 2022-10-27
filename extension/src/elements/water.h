#ifndef WATER_H
#define WATER_H

#include "element.h"
#include <stdlib.h>

class Water: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        // Evaporation
        if (sim->touch_count(row, col, 5)) {
            sim->set_cell(row, col, 6);
            return;
        }

        int dir = (std::rand() % 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row + 1, col);
        }
    }

    double get_density() override {
        return 1.0;
    }
};

#endif // WATER_H