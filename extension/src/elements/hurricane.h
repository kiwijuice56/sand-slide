#ifndef HURRICANE_H
#define HURRICANE_H

#include "element.h"

class Hurricane: public Element {
public:
    const double DECAY = 1.0 / 300;
    const double THUNDER = 0.25;
    const double RAIN = 0.45; 
    const double UP = 0.65;
    const double PRECIPITATE = 1.0 / 48;
    const double GROW = 1.0 / 360;

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
        
        int newRow = row;
        int newCol = col + (int) (sim->randf() * 3) - 1;
        if (sim->randf() < UP) {
            newRow--;
        } else {
            newRow++;
        }

        if (sim->in_bounds(newRow, newCol) && sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 64.0) {
            sim->move_and_swap(row, col, newRow, newCol);
        } else if (sim->randf() < PRECIPITATE) {
            sim->grow(row + 1, col, 0, 3);
        } else if (sim->randf() < GROW) {
            sim->grow(row + 1, col + 1, 0, 41);
            sim->grow(row + 1, col - 1, 0, 41);
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