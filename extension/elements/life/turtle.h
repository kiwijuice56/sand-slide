#pragma once


#include "../element.h"

class Turtle: public Element {
public:
    const double FIRE = 1.0 / 64;
    const double POISON = 1.0 / 8;
    const double MOVE = 1.0 / 8;
    const double CARVE = 1.0 / 8;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FIRE && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        } else if (sim->randf() < POISON && (sim->is_poisoned(row, col) || sim->is_cold(row, col))) {
            sim->set_cell(row, col, 16);
            return;
        } else if (sim->randf() < MOVE) {
            int new_col = col;
            int new_row = row;
            int dir = sim->randf() < 0.5 ? 1 : -1;
            if (sim->randf() < 0.5) {
                new_col += dir;
            } else {
                new_row += dir;
            }

            if (!sim->in_bounds(new_row, new_col)) {
                return;
            }

            if (!(sim->get_cell(new_row, new_col) == 0 ||
            sim->randf() < CARVE && (
            sim->get_cell(new_row, new_col) == 79 ||
            sim->get_cell(new_row, new_col) == 51 ||
            sim->get_cell(new_row, new_col) == 80 ||
            sim->get_cell(new_row, new_col) == 78 ||
            sim->get_cell(new_row, new_col) == 27)))  {
                return;
            }
            const int COLOR[] = {79, 51, 80, 78, 27};
            sim->set_cell(row, col, COLOR[int(sim->time * 32) % 5]);
            sim->set_cell(new_row, new_col, 130);
        }

    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.8;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

