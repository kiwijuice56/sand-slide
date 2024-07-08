#pragma once


#include "../element.h"

class IceExplosion: public Element {
public:
    const double PROCESS = 1.0 / 4;
    const double DECAY = 1.0 / 16;
    const double EXTINGUISH = 1.0 / 2;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the explosion down
        if (sim->randf() > PROCESS) {
            return;
        } else if (sim->randf() < EXTINGUISH && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 89);
        // We eliminate explosions that reach the end, as they tend to linger for a long time if not checked
        } else if (sim->randf() < DECAY || sim->touch_count(row, col, 89) > 1 ||
            row == sim->get_height() - 1 || col == sim->get_width() - 1 || col == 0 || row == 0) {
            sim->set_cell(row, col, 89);
        } else {
            sim->grow(row + 1, col, -1, 88);
            sim->grow(row - 1, col, -1, 88);
            sim->grow(row, col + 1, -1, 88);
            sim->grow(row, col - 1, -1, 88);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.0;
    }

    double get_acid_resistance() override {
        return 0.0;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return -1;
    }

    int get_toxicity() override {
        return 0;
    }
};

