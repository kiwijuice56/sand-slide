#pragma once


#include "../element.h"

class Megido: public Element {
public:
    float FIREWORK = 1.0 / 16;
    float REACT = 1.0 / 4;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 149) >= 4) {
            return;
        }

        if (sim->randf() < REACT) {
            for (int y = row - 5; y <= row + 5; y++) {
                for (int x = col - 5; x <= col + 5; x++) {
                    if (sim->randf() >= REACT || !sim->in_bounds(y, x) || sim->get_cell(y, x) == 149)
                        continue;

                    int dirRow = row - y < 0 ? -1 : 1;
                    int dirCol = col - x < 0 ? -1 : 1;
                    if (row == y) dirRow = 0;
                    if (col == x) dirCol = 0;
                    sim->move_and_swap(y, x, y + dirRow, x + dirCol);
                }
            }
        }

        if (sim->randf() < REACT) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (sim->in_bounds(row + i, col + j) && sim->get_cell(row + i, col + j) != 0) {
                        sim->set_cell(row + i, col + j, 149);
                    }
                }
            }
        }

        if (sim->is_on_fire(row, col) && sim->randf() < REACT) {
            sim->set_cell(row, col, 5);
            return;
        }

        if (sim->is_on_fire(row, col) && sim->randf() < REACT * REACT * REACT) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (y * y + x * x > 49) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 66 : 9);
                    }
                }
            }
        }
    }

    double get_density() override {
        return 9999.0;
    }

    double get_explode_resistance() override {
        return 0.0;
    }

    double get_acid_resistance() override {
        return 0.0;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

