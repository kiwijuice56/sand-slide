#ifndef GRASS_H
#define GRASS_H

#include "element.h"

class Grass: public Element {
public:
    const double GROW = 1 / 8000.0;
    const double FLAME = 1.0 / 16;
    const double LEFT = 0.1;
    const double RIGHT = 0.2;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        if (randf() < GROW) {
            int newCol = col;
            double r = randf();
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
        } else if (sim->touch_count(row, col, 10)) {
            sim->set_cell(row, col, 16);
        }
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // GRASS_H