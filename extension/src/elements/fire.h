#ifndef FIRE_H
#define FIRE_H

#include "element.h"

class Fire: public Element {
public:
    const double DECAY = 1.0 / 90; 

    void process(SandSimulation *sim, int row, int col) override {
        // Extinguish 
        if (sim->touch_count(row, col, 3)) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (randf() < DECAY) {
            sim->set_cell(row, col, 6);
        }

        int dir = (std::rand() % 3) - 1;
        if (dir != 0) {
            sim->move_and_swap(row, col, row, col + dir);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 0.5;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // FIRE_H