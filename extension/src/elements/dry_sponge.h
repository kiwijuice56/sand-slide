#ifndef DRY_SPONGE_H
#define DRY_SPONGE_H

class SandSimulation;

#include "element.h"

class DrySponge: public Element {
public:
    const double GRAB = 1.0 / 32;
    const double PROCESS = 1.0 / 16;
    const double WETTEN = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= PROCESS) 
            return;
        
        for (int y = row - 3; y <= row + 3; y++) {
            for (int x = col - 3; x <= col + 3; x++) { 
                if (sim->in_bounds(y, x) && (sim->get_cell(y, x) == 3 || sim->get_cell(y, x) == 59 || sim->get_cell(y, x) == 71)) { 
                    sim->set_cell(y, x, 0);
                    if (sim->randf() < WETTEN) {
                        sim->set_cell(row, col, 100);
                        return;
                    }
                }
            }
        }

        if (sim->cardinal_touch_count(row, col, 0) == 0) 
            return;
        
        // Keep moving particles closer into the black hole
        for (int y = row - 8; y <= row + 8; y++) {
            for (int x = col - 8; x <= col + 8; x++) {
                if (sim->randf() >= GRAB || !(sim->in_bounds(y, x) && (sim->get_cell(y, x) == 3 || sim->get_cell(y, x) == 59 || sim->get_cell(y, x) == 71))) 
                    continue;
                
                int dirRow = row - y < 0 ? -1 : 1;
                int dirCol = col - x < 0 ? -1 : 1;
                if (row == y) dirRow = 0;
                if (col == x) dirCol = 0;
                sim->move_and_swap(y, x, y + dirRow, x + dirCol);
            }
        }
    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // DRY_SPONGE_H