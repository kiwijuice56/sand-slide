#pragma once




#include "../element.h"

class InfoPistonUpCharged: public Element {
public:
    const double MOVE = 1.0 / 32;
    const double LOSE_CHARGE = 1.0 / 3;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < LOSE_CHARGE) {
            sim->set_cell(row, col, 106);
            return;
        }
        if (sim->randf() < MOVE) {
            int end_row = row;
            while (end_row >= 0 && sim->get_cell(end_row, col) != 0 && sim->get_cell(end_row, col) != 15) {
                end_row--;
            }
            if (end_row == -1 || sim->get_cell(end_row, col) == 15) {
                return;
            }

            while (end_row < row) {
                if (end_row != sim->get_height())
                    sim->set_cell(end_row, col, sim->get_cell(end_row + 1, col));
                end_row++;
            }
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.99;
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

