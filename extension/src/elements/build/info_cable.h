#ifndef INFO_CABLE_H
#define INFO_CABLE_H

class SandSimulation;

#include "../element.h"

class InfoCable: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        for (int i = 0; i < 7; i++) {
            int new_row = row + (sim->randf() < 0.435 ? 1 : -1);
            int new_col = col + (sim->randf() < 0.5 ? 1 : -1);
            if (sim->in_bounds(new_row, new_col) && sim->get_cell(new_row, new_col) == 103) {
                sim->set_cell(new_row, new_col, 102);
                sim->set_cell(row, col, 103);
                row = new_row;
                col = new_col;
            }
        }
        if (sim->touch_count(row, col, 104) > 0) {
            sim->set_cell(row, col, 103);
        }
    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.99;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // INFO_CABLE_H