#ifndef ELECTRICITY_STORM_H
#define ELECTRICITY_STORM_H

#include "element.h"

class ElectricityStorm: public Element {
public:
    const double DOWN = 1 / 1.20;

    void process(SandSimulation *sim, int row, int col) override {
        int n_count = sim->touch_count(row, col, 0) + sim->touch_count(row, col, 39) + 
        sim->touch_count(row, col, 6) + sim->touch_count(row, col, 22);
        if (n_count <= 6) {
            sim->set_cell(row, col, 40);
        } else {
            int rand_row = row + (randf() < DOWN ? 1 : -1);
            int rand_col = col + (std::rand() % 3) - 1;
            sim->set_cell(row, col, 0);
            if (sim->touch_count(rand_row, rand_col, 39) <= 1) {
                sim->grow(rand_row, rand_col, 0, 39);
                sim->grow(rand_row, rand_col, 6, 39);
                sim->grow(rand_row, rand_col, 22, 39);
            }
            sim->set_cell(row, col, 39);
        }
    }

    double get_density() override {
        return 0.01;
    }

    double get_explode_resistance() override {
        return 0.5;
    }

    double get_acid_resistance() override {
        return 0.2;
    }
};

#endif // ELECTRICITY_H