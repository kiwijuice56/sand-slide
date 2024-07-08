#pragma once


#include "../element.h"

class Nanobot: public Element {
public:
    const double FRY = 1 / 16.0;
    const double PROCESS = 1 / 2.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FRY && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0 || sim->touch_count(row, col, 3) > 0 || sim->is_on_fire(row, col))) {
            sim->set_cell(row, col, 9);
            return;
        }

        if (sim->cardinal_touch_count(row, col, 0) == 4) {
            sim->move_and_swap(row, col, row + 1, col);
            return;
        }

        if (sim->randf() >= PROCESS || sim->is_cold(row, col)) {
            return;
        }

        if (sim->in_bounds(row + 1, col) && (sim->get_cell(row + 1, col) == 23 || sim->get_cell(row + 1, col) == 32 || sim->get_cell(row + 1, col) == 101 || sim->get_cell(row + 1, col) == 158 || sim->get_cell(row + 1, col) == 164 || sim->get_cell(row + 1, col) == 129)) {
            sim->grow(row + 1, col, -1, 94);
        }

        // Is there a floor?
        if (is_wall(sim, row, col, row + 1, col)) {
            if (sim->is_swappable(row, col, row + 1, col + 1)) {
                sim->move_and_swap(row, col, row + 1, col + 1); return;
            } else if (sim->is_swappable(row, col, row, col + 1)) {
                sim->move_and_swap(row, col, row, col + 1); return;
            } else if (sim->is_swappable(row, col, row - 1, col + 1)) {
                sim->move_and_swap(row, col, row - 1, col + 1); return;
            } else if (sim->is_swappable(row, col, row - 1, col)) {
                sim->move_and_swap(row, col, row - 1, col); return;
            }
        }

        // Is there a ceiling?
        else if (is_wall(sim, row, col, row - 1, col)) {
            if (sim->is_swappable(row, col, row - 1, col - 1)) {
                sim->move_and_swap(row, col, row - 1, col - 1); return;
            } else if (sim->is_swappable(row, col, row, col - 1)) {
                sim->move_and_swap(row, col, row, col - 1); return;
            } else if (sim->is_swappable(row, col, row + 1, col - 1)) {
                sim->move_and_swap(row, col, row + 1, col - 1); return;
            } else if (sim->is_swappable(row, col, row + 1, col)) {
                sim->move_and_swap(row, col, row + 1, col); return;
            }
        }

        // Is there a wall on the right?
        else if (is_wall(sim, row, col, row, col + 1)) {
            if (sim->is_swappable(row, col, row - 1, col + 1)) {
                sim->move_and_swap(row, col, row - 1, col + 1); return;
            } else if (sim->is_swappable(row, col, row - 1, col)) {
                sim->move_and_swap(row, col, row - 1, col); return;
            }
        }

        // Is there a wall on the left?
        else if (is_wall(sim, row, col, row, col - 1)) {
            if (sim->is_swappable(row, col, row + 1, col - 1)) {
                sim->move_and_swap(row, col, row + 1, col - 1); return;
            } else if (sim->is_swappable(row, col, row + 1, col)) {
                sim->move_and_swap(row, col, row + 1, col); return;
            }
        }

        sim->move_and_swap(row, col, row + (int) (sim->randf() * 3) - 1, col + (int) (sim->randf() * 3) - 1);
    }

    bool is_wall(SandSimulation *sim, int row1, int col1, int row2, int col2) {
        return !sim->in_bounds(row2, col2) || sim->get_cell(row2, col2) == 95 || !sim->is_swappable(row1, col1, row2, col2);
    }

    double get_density() override {
        return 5.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 1.0;
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

