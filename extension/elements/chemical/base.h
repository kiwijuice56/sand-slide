#pragma once


#include "../element.h"

class Base: public Element {
public:
    const double DECAY = 1.0 / 4098;
    const double EVAPORATE = 1.0 / 64;
    const double EAT = 1.0 / 16;
    const double EMIT = 1.0 / 64;
    const double DOWN = 1.0 / 1.2;
    const double DOWN_BLOCK = 1.0 / 16;
    const double MIX = 1.0 / 2;
    const double REACT = 1.0 / 2;

    void process(SandSimulation *sim, int row, int col) override {
        // Decay
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 22);
            return;
        }

        if (sim->is_cold(row, col)) {
            sim->set_cell(row, col, 155);
            return;
        }

        sim->liquid_process(row, col, 2);

        bool blocked = !sim->in_bounds(row + 1, col) || sim->get_cell(row + 1, col) == 3;
        int new_row = row, new_col = col;

        if (sim->randf() < (blocked ? DOWN_BLOCK : DOWN))
            new_row++;
        else
            new_col += sim->randf() < 0.5 ? 1 : -1;

        // Ensure that the swallowed cell is in bounds and not base
        if (!sim->in_bounds(new_row, new_col) || sim->get_cell(new_row, new_col) == 133)
            return;

        // Swap and delete
        if (sim->get_cell(new_row, new_col) == 0 || sim->randf() < EAT * (1.0 - sim->elements.at(sim->get_cell(new_row, new_col))->get_acid_resistance())) {
            sim->set_cell(new_row, new_col, sim->get_cell(row, col));
            sim->set_cell(row, col, sim->randf() < EMIT ? 22 : 0);
        }

        if (sim->randf() < MIX && sim->touch_count(row, col, 21) + sim->touch_count(row, col, 59) > 0) {
            sim->set_cell(row, col, 3);
        }
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

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

