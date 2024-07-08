#pragma once


#include "../element.h"

class MushroomStem: public Element {
public:
    const double GROW = 1.0 / 128;
    const double FLOWER = 1.0 / 1024;
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

        int type = sim->randf() < 0.5 ? 1 : 0;
        if (sim->randf() < GROW) {
            if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) == 168) {
                return;
            }
            if (sim->in_bounds(row, col - 1) && sim->get_cell(row, col - 1) == 168) {
                return;
            }
            sim->grow(row - 1, col, 0, 169);
            sim->grow(row - 1, col, 3, 169);
        } else if (sim->randf() < FLOWER) {
            if (!(sim->in_bounds(row - 1, col) && (sim->get_cell(row - 1, col) == 3 || sim->get_cell(row - 1, col) == 0))) {
                return;
            }
            for (int y = -4; y <= -1; y++) {
                for (int x = -2; x <= 2; x++) {
                    if (y == -4 && (x == -2 || x == 2)) {
                        continue;
                    }
                    if (!sim->in_bounds(row + y, col + x)) {
                        continue;
                    }
                    if (!(sim->get_cell(row + y, col + x) == 0 || sim->get_cell(row + y, col + x) == 3 || sim->get_cell(row + y, col + x) == 169)) {
                        continue;
                    }
                    if (type == 0) {
                        sim->set_cell(row + y, col + x, 170);
                    } else {
                        sim->set_cell(row + y, col + x, sim->randf() < 0.8 ? 171 : 172);
                    }
                }
            }
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

