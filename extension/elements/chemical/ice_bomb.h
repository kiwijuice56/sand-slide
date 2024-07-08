#pragma once




#include "../element.h"

class IceBomb: public Element {
public:
    const double IGNITE = 0.05;
    const double MELT = 1.0 / 32;
    const double FIREWORK = 1.0 / 8;
    const double DECAY = 1.0 / 1024;
    const double GROW = 1.0 / 256;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 96);
            return;
        }
        if (sim->randf() < GROW) {
            sim->grow(row + 1, col, 0, 96);
            sim->grow(row - 1, col, 0, 96);
            sim->grow(row, col + 1, 0, 96);
            sim->grow(row, col - 1, 0, 96);
        }

        if (sim->randf() < MELT && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 96);
            return;
        }

        // Explode
        if (sim->randf() < IGNITE && sim->touch_count(row, col, 88) + sim->touch_count(row, col, 3) > 0) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (y * y + x * x > 36) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 90 : 88);
                    }
                }
            }

        }
    }

    double get_density() override {
        return 16.0;
    }

    double get_explode_resistance() override {
        return 0.08;
    }

    double get_acid_resistance() override {
        return 0.65;
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

