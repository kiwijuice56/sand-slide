#ifndef OXIDIZED_POTASSIUM_H
#define OXIDIZED_POTASSIUM_H

#include "element.h"

class OxidizedPotassium: public Element {
public:
    const double FLAME = 1 / 64.0;
    const double WATER = 1 / 32.0;
    const double PLASMA = 1 / 18.0;
    const double POWDER = 1 / 1.025;
    const double OXIDIZE_A = 1 / 16;
    const double OXIDIZE_B = 1 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 60, 38);
            sim->grow(row - 1, col, 60, 38);
            sim->grow(row, col - 1, 60, 38);
            sim->grow(row, col + 1, 60, 38);
            return;
        }

        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 61);
        }
        
        if (sim->randf() < WATER && sim->touch_count(row, col, 3)) {
            for (int y = -3; y <= 3; y++) {
                for (int x = -3; x <= 3; x++) {
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, 46);
                    }
                }
            }
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 6.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.89;
    }
};

#endif // OXIDIZED_POTASSIUM_H