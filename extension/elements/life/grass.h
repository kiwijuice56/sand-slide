#pragma once


#include "../element.h"

class Grass: public Element {
public:
    const double GROW = 1.0 / 1024;
    const double FLAME = 1.0 / 16;
    const double LEFT = 0.1;
    const double RIGHT = 0.2;
    const double POISON = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        } else if (sim->randf() < POISON && sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        if (sim->randf() < GROW) {
            int newCol = col;
            double r = sim->randf();
            if (r < LEFT) {
                newCol--;
            } else if (r < RIGHT) {
                newCol++;
            }

            sim->grow(row - 1, newCol, 0, 14);
            sim->grow(row - 1, newCol, 3, 14);
            sim->grow(row - 1, newCol, 11, 14);
            sim->grow(row - 1, newCol, 12, 14);
            sim->grow(row - 1, newCol, 13, 14);
        }
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.2;
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

