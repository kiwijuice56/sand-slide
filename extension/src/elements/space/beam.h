#ifndef BEAM_H
#define BEAM_H

#include "../element.h"

class Beam: public Element {
public:
    const double DECAY = 1.0 / 2;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != 94) {
            sim->set_cell(row, col, 0);
            return;
        }
        sim->grow(row + 1, col, -1, 94);
        sim->grow(row + 2, col, -1, 94);
        sim->grow(row + 3, col, -1, 94);
    }

    double get_density() override {
        return 128.0;
    }

    double get_explode_resistance() override {
        return 1.0;
    }

    double get_acid_resistance() override {
        return 1.0;
    }
};

#endif // BEAM_H