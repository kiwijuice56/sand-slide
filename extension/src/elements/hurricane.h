#ifndef HURRICANE_H
#define HURRICANE_H

#include "element.h"

class Hurricane: public Element {
public:
    const double DECAY = 1.0 / 180;
    const double THUNDER = 0.15;
    const double RAIN = 0.45; 

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            double x = sim->randf();
            if (x < THUNDER)
                sim->set_cell(row, col, 37);
            else if (x < RAIN)
                sim->set_cell(row, col, 3);
            else
                sim->set_cell(row, col, 0);
        }
        
        int newRow = row + (int) (sim->randf() * 3) - 1;
        int newCol = col + (int) (sim->randf() * 3) - 1;

        if (sim->in_bounds(newRow, newCol) && sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 64.0) {
            sim->move_and_swap(row, col, newRow, newCol);
        } 
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.1;
    }
};

#endif // HURRICANE_H