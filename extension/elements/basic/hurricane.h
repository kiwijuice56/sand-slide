#pragma once


#include "../element.h"

class Hurricane: public Element {
public:
    const double DECAY = 1.0 / 500;
    const double THUNDER = 0.25;
    const double RAIN = 0.65;
    const double UP = 0.65;
    const double PRECIPITATE = 1.0 / 48;
    const double GROW = 1.0 / 128;

    void process(SandSimulation *sim, int row, int col) override {
        // Decay into either rain, nothing, or thunder
        if (sim->randf() < DECAY) {
            double x = sim->randf();
            if (x < THUNDER)
                sim->set_cell(row, col, 37);
            else if (x < RAIN)
                sim->set_cell(row, col, 3);
            else
                sim->set_cell(row, col, 0);
        }

        int newRow = row;
        int newCol = col + (int) (sim->randf() * 3) - 1;
        if (sim->randf() < UP) {
            newRow--;
        } else {
            newRow++;
        }

        if (sim->in_bounds(newRow, newCol) && sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 64.0) {
            sim->set_cell(row, col, sim->get_cell(newRow, newCol));
            sim->set_cell(newRow, newCol, 41);
        } else if (sim->randf() < PRECIPITATE) {
            sim->grow(row + 1, col, 0, 3);
        } else if (sim->randf() < GROW) {
            sim->grow(row + 1, col + 1, 0, 41);
            sim->grow(row + 1, col - 1, 0, 41);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.1;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

