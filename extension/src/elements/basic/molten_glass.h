#ifndef MOLTEN_GLASS_H
#define MOLTEN_GLASS_H



#include "../element.h"

class MoltenGlass: public Element {
public:
    const double COOL = 1.0 / 32;
    const double SPREAD = 1.0 / 48;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < COOL || sim->is_cold(row, col)) {
            sim->set_cell(row, col, 25);
            return;
        }
        
        if (sim->randf() < SPREAD) {
            sim->grow(row + 1, col, 1, 53);
            sim->grow(row - 1, col, 1, 53);
            sim->grow(row, col - 1, 1, 53);
            sim->grow(row, col + 1, 1, 53);
        }
    }

    double get_density() override {
        return 3.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.95;
    }

    int get_state() override {
        return 0;
    }
};

#endif // MOLTEN_GLASS_H