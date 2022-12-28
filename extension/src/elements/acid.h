#ifndef ACID_H
#define ACID_H

#include "element.h"
#include <stdlib.h>

class Acid: public Element {
public:
    const double DECAY_AIR = 1.0 / 256;
    const double DECAY = 1.0 / 1024;
    const double EVAPORATE = 1.0 / 64;
    const double EAT = 1.0 / 8;
    const double MIX = 1.0 / 4;
    const double EMIT = 1.0 / 64;
    const double DOWN = 1.0 / 1.2;
    const double DOWN_BLOCK = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Decay
        if (sim->randf() < DECAY_AIR && sim->touch_count(row, col, 0) > 0 || sim->randf() < DECAY) {
            sim->set_cell(row, col, 22);
            return;
        }

        // Evaporate into acid gas
        if (sim->randf() < EVAPORATE && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 22);
            return;
        }

        // Mix with water to turn into acidic water
        if (sim->randf() < MIX && sim->touch_count(row, col, 3) > 0) {
            sim->set_cell(row, col, 59);
            return;
        }

        sim->liquid_process(row, col, 2); 

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 3;
        int new_row = row, new_col = col;

        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN)) 
            new_row++;
        else 
            new_col += sim->randf() < 0.5 ? 1 : -1;

        // Ensure that the swallowed cell is in bounds and not acid
        if (!sim->in_bounds(new_row, new_col) || sim->get_cell(new_row, new_col) == 21 || sim->get_cell(new_row, new_col) == 59)
            return;

        // Swap and delete
        if (sim->get_cell(new_row, new_col) == 0 || sim->randf() < EAT * (1.0 - sim->elements.at(sim->get_cell(new_row, new_col))->get_acid_resistance())) {
            sim->move_and_swap(row, col, new_row, new_col);
            sim->set_cell(row, col, sim->randf() < EMIT ? 22 : 0);
        }

        if (sim->randf() < EMIT) 
            sim->grow(row - 1, col, 0, 22);
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 1.0;
    }
};

#endif // ACID_H